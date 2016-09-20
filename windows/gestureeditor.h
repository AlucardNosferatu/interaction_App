#ifndef GESTUREEDITOR_H
#define GESTUREEDITOR_H

#include <QMainWindow>
#include <gesturelib.h>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QFileDialog>

namespace Ui {
class GestureEditor;
}

class GestureEditor : public QMainWindow
{
    Q_OBJECT

public:
    GestureEditor(QWidget *parent,GestureLib &g);
    ~GestureEditor();
    int setGesturelib(GestureLib &g);

private slots:
    void on_gestureList_clicked(const QModelIndex &index);
    void on_angleCiteriaList_clicked(const QModelIndex &index);
    void on_movementCiteriaList_clicked(const QModelIndex &index);
    void on_axisCiteriaList_clicked(const QModelIndex &index);
    void on_newAxisButton_clicked();
    void on_deleteAxisButton_clicked();
    void on_updateAxisButton_clicked();
    void on_saveLibButton_clicked();
    void on_newAngleButton_clicked();
    void on_deleteAngleButton_clicked();
    void on_updateAngleButton_clicked();
    void on_newMoveButton_clicked();
    void on_deleteMoveButton_clicked();
    void on_updateMoveButton_clicked();
    void on_newGestureButton_clicked();
    void on_deleteGestureButton_clicked();
    void on_updateGestureButton_clicked();
    void on_loadLibButton_clicked();
    void on_addDefaultButton_clicked();

    void on_updateEMGButton_clicked();

private:
    Ui::GestureEditor *ui;

    GestureLib &gesturelib;

    //UI elements
    QStringListModel axisCiteriaListModel,angleCiteriaListModel,moveCiteriaListModel,gestureModel;
    QStandardItemModel moveModel;
};

#endif // GESTUREEDITOR_H
