#include "gestureeditor.h"
#include "ui_gestureeditor.h"

GestureEditor::GestureEditor(QWidget *parent, GestureLib &g) :
    QMainWindow(parent),
    ui(new Ui::GestureEditor),
    gesturelib(g)
{
    ui->setupUi(this);

    QString fileName=QString("default.json");
    QFile file(fileName);
    if (file.exists())
        gesturelib.loadLib(fileName);
    else
        gesturelib.addDefaultGestures();

    gestureModel.setStringList(gesturelib.getGestureList());
    ui->gestureList->setModel(&gestureModel);

    for(int i=0;i<AXISNUM;i++)
        ui->axisBox->addItem(QString(axisNames[i]));

    for(int i=0;i<JOINTNUM;i++)
    {
        ui->jointBox->addItem(QString(jointNames[i]));
        ui->jointBox2->addItem(QString(jointNames[i]));
    }

    for (int i=0;i<MOVEMENTNUM;i++)
        ui->moveBox->addItem(QString(movementNames[i]));

    for (int i=0;i<EMGTYPENUM+1;i++)
        ui->EMGBox->addItem(QString(EMGNames[i]));
}

GestureEditor::~GestureEditor()
{
    delete ui;
}

void GestureEditor::on_gestureList_clicked(const QModelIndex &index)
{
    axisCiteriaListModel.setStringList(gesturelib.getGestureAxisCiteriaAt(index.row()));
    ui->axisCiteriaList->setModel(&axisCiteriaListModel);

    angleCiteriaListModel.setStringList(gesturelib.getGestureAngleCiteriaAt(index.row()));
    ui->angleCiteriaList->setModel(&angleCiteriaListModel);

    moveCiteriaListModel.setStringList(gesturelib.getGestureMoveCiteriaAt(index.row()));
    ui->movementCiteriaList->setModel(&moveCiteriaListModel);

    ui->nameEdit->setText(gesturelib.getGestureAt(index.row()).name());
    ui->commandEdit->setText(gesturelib.getGestureAt(index.row()).command());
    ui->descriptionEdit->setPlainText(gesturelib.getGestureAt(index.row()).description());

    Gesture g = gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    ui->EMGBox->setCurrentIndex(g.getEMGGesture()+1);
}

void GestureEditor::on_angleCiteriaList_clicked(const QModelIndex &index)
{
    Gesture g = gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    ui->jointBox->setCurrentIndex(g.getAngleCiterionAt(index.row()).joint());
    ui->angleEdit->setText(QString("%1").arg(g.getAngleCiterionAt(index.row()).value()));
}

void GestureEditor::on_movementCiteriaList_clicked(const QModelIndex &index)
{
    Gesture g = gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    ui->jointBox2->setCurrentIndex(g.getMoveCiterionAt(index.row()).joint());
    ui->moveBox->setCurrentIndex(g.getMoveCiterionAt(index.row()).move());
}

void GestureEditor::on_axisCiteriaList_clicked(const QModelIndex &index)
{
    Gesture g = gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    ui->axisBox->setCurrentIndex(g.getAxisCiterionAt(index.row()).axis());
    ui->xEdit->setText(QString("%1").arg(g.getAxisCiterionAt(index.row()).x()));
    ui->yEdit->setText(QString("%1").arg(g.getAxisCiterionAt(index.row()).y()));
    ui->zEdit->setText(QString("%1").arg(g.getAxisCiterionAt(index.row()).z()));
}

void GestureEditor::on_newAxisButton_clicked()
{
    Gesture &g=gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    g.addAxisCiterion(NEWAXIS,0,0,0);
    axisCiteriaListModel.setStringList(g.getAxisCiteriaList());
}

void GestureEditor::on_deleteAxisButton_clicked()
{
    Gesture &g=gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    g.removeAxisCiterionAt(ui->axisCiteriaList->currentIndex().row());
    axisCiteriaListModel.setStringList(g.getAxisCiteriaList());
}

void GestureEditor::on_updateAxisButton_clicked()
{
    Axes axis=(Axes)ui->axisBox->currentIndex();
    double x=ui->xEdit->text().toDouble();
    double y=ui->yEdit->text().toDouble();
    double z=ui->zEdit->text().toDouble();
    double norm=sqrt(x*x+y*y+z*z);
    x=x/norm;
    y=y/norm;
    z=z/norm;
    Gesture &g=gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    g.updateAxisCiterionAt(ui->axisCiteriaList->currentIndex().row(),axis,x,y,z);
    axisCiteriaListModel.setStringList(g.getAxisCiteriaList());
}

void GestureEditor::on_saveLibButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
         tr("Save"),
         "",
         tr("鏁版嵁鏂囦欢 (*.json)"));
    if (!fileName.isNull())
        gesturelib.saveLib(fileName);
}

void GestureEditor::on_newAngleButton_clicked()
{
    Gesture &g=gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    g.addAngleCiterion(NEWJOINT,0);
    angleCiteriaListModel.setStringList(g.getAngleCiteriaList());
}

void GestureEditor::on_deleteAngleButton_clicked()
{
    Gesture &g=gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    g.removeAngleCiterionAt(ui->angleCiteriaList->currentIndex().row());
    angleCiteriaListModel.setStringList(g.getAngleCiteriaList());
}

void GestureEditor::on_updateAngleButton_clicked()
{
    Joint joint = (Joint)ui->jointBox->currentIndex();
    double value= ui->angleEdit->text().toDouble();
    Gesture &g=gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    g.updateAngleCiterionAt(ui->angleCiteriaList->currentIndex().row(),joint,value);
    angleCiteriaListModel.setStringList(g.getAngleCiteriaList());
}

void GestureEditor::on_newMoveButton_clicked()
{
    Gesture &g=gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    g.addMovementCiterion(NEWJOINT,NOMOVEMENT);
    moveCiteriaListModel.setStringList(g.getMoveCiteriaList());
}

void GestureEditor::on_deleteMoveButton_clicked()
{
    Gesture &g=gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    g.removeMovementCiterionAt(ui->movementCiteriaList->currentIndex().row());
    moveCiteriaListModel.setStringList(g.getMoveCiteriaList());
}

void GestureEditor::on_updateMoveButton_clicked()
{
    Joint joint=(Joint) ui->jointBox2->currentIndex();
    MovementType move=(MovementType) ui->moveBox->currentIndex();
    Gesture &g=gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    g.updateMovementCiterionAt(ui->movementCiteriaList->currentIndex().row(),joint,move);
    moveCiteriaListModel.setStringList(g.getMoveCiteriaList());
}

void GestureEditor::on_newGestureButton_clicked()
{
    gesturelib.addEmptyGesture();
    gestureModel.setStringList(gesturelib.getGestureList());
}

void GestureEditor::on_deleteGestureButton_clicked()
{
    gesturelib.removeGestureAt(ui->gestureList->currentIndex().row());
    gestureModel.setStringList(gesturelib.getGestureList());
    angleCiteriaListModel.setStringList(QStringList());
    axisCiteriaListModel.setStringList(QStringList());
    moveCiteriaListModel.setStringList(QStringList());
}

void GestureEditor::on_updateGestureButton_clicked()
{
    Gesture &g=gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    g.updateGesture(ui->nameEdit->text().toUpper(),ui->commandEdit->text().toUpper(),ui->descriptionEdit->toPlainText());
    gestureModel.setStringList(gesturelib.getGestureList());
}

void GestureEditor::on_loadLibButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,
                tr("导入手势库"),
                "",
                tr("手势文件 (*.json)"));
    if (!fileName.isNull())
        gesturelib.loadLib(fileName);
    gestureModel.setStringList(gesturelib.getGestureList());
}

void GestureEditor::on_addDefaultButton_clicked()
{
    gesturelib.addDefaultGestures();
    gestureModel.setStringList(gesturelib.getGestureList());
}

void GestureEditor::on_updateEMGButton_clicked()
{
    Gesture &g=gesturelib.getGestureAt(ui->gestureList->currentIndex().row());
    g.setEMGCiterion(ui->EMGBox->currentIndex()-1);
}
