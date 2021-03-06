#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_SelectFilePushButton_clicked()
{
  switch (SelectFileMode(ui->ModeButtonGroup->checkedId()))
  {
    case SelectFileMode::Static:

      ui->DirectoryLineEdit->setText(QFileDialog::getOpenFileName(this, tr("Open File"), "C:/",
                                                                  tr("All (*.*);;Images (*.png *.xpm *.jpg);;Text "
                                                                     "files (*.txt "
                                                                     "*.doc *.docx);;XML files "
                                                                     "(*.xml)")));
      break;
    case SelectFileMode::Custom:
      QFileDialog dialog(this);
      dialog.setFileMode(QFileDialog::AnyFile);
      dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg);;Text files (*.txt "
                              "*.doc *.docx *.pdf);;XML files "
                              "(*.xml)"));
      dialog.setViewMode(QFileDialog::Detail);
      dialog.setWindowTitle("Choose File");
      dialog.setLabelText(QFileDialog::Accept, "Choose");
      dialog.setLabelText(QFileDialog::Reject, "Cancel");
      if (dialog.exec())
        ui->DirectoryLineEdit->setText(dialog.selectedFiles().at(0));
      break;
  }
  ptr = std::make_unique<File>();
  ptr->SetPath(ui->DirectoryLineEdit->text());
}

void MainWindow::on_SelectDirectoryPushButton_clicked()
{
  ui->DirectoryLineEdit->setText(QFileDialog::getExistingDirectory(
      this, tr("Open Directory"), "C:/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
  ptr = std::make_unique<Directory>();
  ptr->SetPath(ui->DirectoryLineEdit->text());
}

void MainWindow::on_PrintPushButton_clicked()
{
  if (!ui->DirectoryLineEdit->text().isEmpty())
    ui->plainTextEdit->setPlainText(ptr->Print());
}
