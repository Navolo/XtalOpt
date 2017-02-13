/**********************************************************************
  LocalQueueInterfaceConfigDialog

  Copyright (C) 2011 by David C. Lonie

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation version 2 of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 ***********************************************************************/

// Don't document this:
/// @cond

#include <globalsearch/queueinterfaces/localdialog.h>

#include <globalsearch/optbase.h>
#include <globalsearch/queueinterfaces/local.h>
#include <globalsearch/ui/abstractdialog.h>

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

#include <QtCore/QObject>

namespace GlobalSearch {

  LocalQueueInterfaceConfigDialog::LocalQueueInterfaceConfigDialog
  (AbstractDialog *parent, OptBase *opt, LocalQueueInterface *o)
    : QDialog(parent),
      m_opt(opt),
      m_queueInterface(o),
      m_edit_workdir(0),
      m_edit_description(0)
  {
    m_vlayout = new QVBoxLayout(this);

    // Create workdir prompt
    m_workdir_layout = new QHBoxLayout();

    m_label1 = new QLabel(tr("Local working directory:"), this);
    m_workdir_layout->addWidget(m_label1);

    m_edit_workdir = new QLineEdit(this);
    m_workdir_layout->addWidget(m_edit_workdir);

    m_vlayout->addItem(m_workdir_layout);

    // Create description prompt
    m_desc_layout = new QHBoxLayout();

    m_label2 = new QLabel(tr("Search description:"), this);
    m_desc_layout->addWidget(m_label2);

    m_edit_description = new QLineEdit(this);
    m_desc_layout->addWidget(m_edit_description);

    m_vlayout->addItem(m_desc_layout);

    // Add checkbox
    m_cb_logErrorDirs = new QCheckBox();

    m_cb_logErrorDirs->setText("Log error directories?");
    m_cb_logErrorDirs->setChecked(m_opt->m_logErrorDirs);
    QString toolTip = tr("When a job fails or has to restart for any reason,"
                         "\nif this is checked, it will create a copy of the "
                         "\nfailed job directory in <localpath>/errorDirs. "
                         "\nThis can assist in figuring out why a job failed. "
                         "\nNote that if a job fails twice, the second "
                         "\nfailure will overwrite the first one.");
    m_cb_logErrorDirs->setToolTip(toolTip);
    m_vlayout->addWidget(m_cb_logErrorDirs);

    // Add spacer
    m_spacer = new QSpacerItem(10,10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_vlayout->addItem(m_spacer);

    m_bbox = new QDialogButtonBox(this);
    m_bbox->setStandardButtons(QDialogButtonBox::Ok |
                               QDialogButtonBox::Cancel );
    m_vlayout->addWidget(m_bbox);

    setLayout(m_vlayout);

    connect(m_bbox, SIGNAL(accepted()),
            this, SLOT(accept()));
    connect(m_bbox, SIGNAL(rejected()),
            this, SLOT(reject()));
  }

  LocalQueueInterfaceConfigDialog::~LocalQueueInterfaceConfigDialog()
  {
    // Delete all child widgets
    QLayoutItem *child;
    while ((child = m_vlayout->takeAt(0)) != 0) {
      delete child->widget();
      delete child;
    }
    // Delete the layout
    delete m_vlayout;
  }

  void LocalQueueInterfaceConfigDialog::accept()
  {
    m_opt->filePath = m_edit_workdir->text().trimmed();
    m_opt->description = m_edit_description->text().trimmed();
    m_opt->m_logErrorDirs = m_cb_logErrorDirs->isChecked();
    QDialog::accept();
    this->close();
  }

  void LocalQueueInterfaceConfigDialog::reject()
  {
    updateGUI();
    QDialog::reject();
    this->close();
  }

  void LocalQueueInterfaceConfigDialog::updateGUI()
  {
    m_edit_workdir->setText(m_opt->filePath);
    m_edit_description->setText(m_opt->description);
  }

} // end namespace GlobalSearch

/// @endcond
