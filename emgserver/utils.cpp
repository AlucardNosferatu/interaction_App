/*************************************************
utils.cpp
Author:Mitom
Date:2019-5-30
Description:����
**************************************************/

#include "sEMG.hpp"
#include "utils.hpp"

//��ȡ�ļ�����
int getFileRowCount(string file)
{
	ifstream infile;
	infile.open(file.data());
	int rowNumber = 0;
	string s;
	while(getline(infile,s)){
		rowNumber++;
	}
	infile.close();
	return rowNumber;
}

//��ȡ�ļ�����
int getFileColCount(string file)
{
	ifstream infile;
	infile.open(file.data());
	//assert(infile.is_open());
	int colNumber = 0;
	string s;
	vector<string> vecRow;
	while(getline(infile,s)){
		vecRow = split(s, " ");
		break;
	}

	colNumber = vecRow.size();
	infile.close();

	return colNumber;
}

//�ַ����ָ��
vector<string> split(string srcStr, const string& delim)
{
	int nPos = 0;
	vector<string> vec;
	nPos = srcStr.find(delim.c_str());
	while(-1 != nPos)
	{
		string temp = srcStr.substr(0, nPos);
		if(temp!="" && temp!=" "){
			vec.push_back(temp);
		}
		srcStr = srcStr.substr(nPos+1);
		nPos = srcStr.find(delim.c_str());
	}
	if(srcStr!="" && srcStr!=" "){
		vec.push_back(srcStr);
	}
	return vec;
}

//����ģ�Ͳ���
Matrix loadEMGData(string file)
{
	ifstream infile;
	infile.open(file.data());
	//assert(infile.is_open());
	int rowCount = getFileRowCount(file);
	int colCount = getFileColCount(file);

	Matrix mat = Matrix(rowCount, colCount);
	double **matPtr = mat.getPtr();

    string s;
    int rowIndex = 0;
    while(getline(infile,s))
    {
        vector<string> ret = split(s, " ");
        for(size_t i=0; i<ret.size(); i++){
        	matPtr[rowIndex][i] = strToDouble(ret[i].c_str());
        }
        rowIndex++;
    }
    infile.close();
    return mat;
}

Filter parseFilterWeight(const char * path, int fsize, int depth, int row, int col)
{
	TiXmlDocument mydoc(path);//xml�ĵ�����
	bool loadOk=mydoc.LoadFile();//�����ĵ�
	if(!loadOk)
	{
		cout<<"could not load the test file.Error:"<<mydoc.ErrorDesc()<<endl;
		exit(1);
	}

	Filter filter = Filter(fsize,depth,row,col);
	TiXmlElement *rootElem = mydoc.RootElement();	// filters
	TiXmlElement *fElem = rootElem;
	int fcount = 0;
	for(TiXmlElement *tensonElem = fElem->FirstChildElement();tensonElem != NULL;tensonElem = tensonElem->NextSiblingElement()){// tensor

		Tensor tensor = Tensor(row,col);
		for(TiXmlElement *matElem = tensonElem->FirstChildElement();matElem != NULL;matElem=matElem->NextSiblingElement()){ // matrix
			Matrix mat = Matrix(row,col);
			int row = 0;
			for(TiXmlElement *rowElem = matElem->FirstChildElement();rowElem != NULL;rowElem=rowElem->NextSiblingElement()){ // row
				mat.getPtr()[row][0] = strToDouble(rowElem->FirstChild()->Value());
				row++;
			}
			tensor.addLayer(mat);
		}
		filter.setFilter(fcount, tensor);
		fcount ++;
	}
	return filter;
}

double strToDouble(string str)
{
	double result;
	istringstream is(str);
	is >> result;
	return result;
}

string intToString(int num)
{
    string str = "";
    ostringstream oss;
    oss << num;
    str = oss.str();
    return str;
}

Matrix parseFullConnWeight(const char * path, int row, int col)
{
	TiXmlDocument mydoc(path);//xml�ĵ�����
	bool loadOk=mydoc.LoadFile();//�����ĵ�
	if(!loadOk)
	{
		cout<<"could not load the test file.Error:"<<mydoc.ErrorDesc()<<endl;
		exit(1);
	}

	Matrix outMat = Matrix(row, col);

	//Filter filter = Filter(fsize,depth,row,col);
	TiXmlElement *rootElem = mydoc.RootElement();
	TiXmlElement *mElem = rootElem;//  mat
	int fcount = 0;
	int rowIndex = 0;
	int colIndex = 0;
	string result;
	for(TiXmlElement *rowElem = mElem->FirstChildElement();rowElem != NULL;rowElem=rowElem->NextSiblingElement()){ // row
		stringstream input(rowElem->FirstChild()->Value());
		while(input>>result){
			//cout << result << endl;
			outMat.getPtr()[rowIndex][colIndex] = strToDouble(result);
			colIndex ++;
		}
		colIndex = 0;
		//input.close();
		rowIndex++;
	}
	return outMat;
}

vector<double> parseBias(const char * path, int num)
{
	TiXmlDocument mydoc(path);//xml�ĵ�����
	bool loadOk=mydoc.LoadFile();//�����ĵ�
	if(!loadOk)
	{
		cout<<"could not load the test file.Error:"<<mydoc.ErrorDesc()<<endl;
		exit(1);
	}
	vector<double> outBias(num);
	TiXmlElement *rootElem = mydoc.RootElement();
	TiXmlElement *mElem = rootElem;
	int fcount = 0;
	int rowIndex = 0;
	int colIndex = 0;
	string result;
	stringstream input(mElem->FirstChild()->Value());
	while(input>>result){
		//cout << result << endl;
		outBias[colIndex] = strToDouble(result);
		colIndex ++;
	}
	//input.close();
	return outBias;
}

void emgDataToMat(Matrix & res, string path)
{
	ifstream infile;
	infile.open(path.data());   //���ļ����������ļ���������
	assert(infile.is_open());   //��ʧ��,�����������Ϣ,����ֹ��������

	int rowCount = getFileRowCount(path);
	int colCount = getFileColCount(path);

	res = Matrix(rowCount, colCount);

	string s;
	int row = 0;
	int col = 0;
	while (getline(infile, s)) {
		istringstream is(s); //��������һ��ת�����������в���
		double d;
		//cout << row << " ";
		while (!is.eof()) {
			is >> d;
			//cout << d << " ";
			res.setValue(row, col, d);
			col ++;
		}
		//cout << endl;
		row ++;
		col = 0;
		s.clear();
	}
	infile.close();             //�ر��ļ�������
}


