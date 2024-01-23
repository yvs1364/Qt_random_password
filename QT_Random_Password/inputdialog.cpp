#include "inputdialog.h"

InputDialog::InputDialog(QWidget *parent) : QDialog(parent){
  // Setup form layout
  QFormLayout *lytMain = new QFormLayout(this);

  // Setup label
  QLabel *tLabel_pass = new QLabel(QString("Password"), this);
  QLabel *tLabel_website = new QLabel(QString("Website"), this);
  // Setup Input
  QLineEdit *tLine_pass = new QLineEdit(this);
  QLineEdit *tLine_website = new QLineEdit(this);

  lytMain->addRow(tLabel_pass, tLine_pass);
  lytMain->addRow(tLabel_website, tLine_website);

  fields << tLine_pass;
  fields << tLine_website;


  QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this );
  lytMain->addWidget(buttonBox);

  bool conn = connect(buttonBox, &QDialogButtonBox::accepted, this, &InputDialog::accept);
  Q_ASSERT(conn);
  conn = connect(buttonBox, &QDialogButtonBox::rejected, this, &InputDialog::reject);
  Q_ASSERT(conn);

  setLayout(lytMain);
}

QStringList InputDialog::getStrings(QWidget *parent, bool *ok){
  InputDialog *dialog = new InputDialog(parent);
  QStringList list;
  const int ret = dialog->exec();

  if (ok){
    *ok = !!ret;
  }

  if (ret) {
    foreach (auto field, dialog->fields) {
      list << field->text();
    }
  }

  dialog->deleteLater();

  return list;
}
