#include "qwcomboboxdelegate.h"

QWComboBoxDelegate::QWComboBoxDelegate()
{

}

void QWComboBoxDelegate::setItems(QStringList items,bool isEdit)
{
    m_itemList = items;
    m_isEdit = isEdit;
}

QWidget *QWComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    QComboBox *editor = new QComboBox(parent);
    for(int i=0; i < m_itemList.count(); ++i)
        editor->addItem(m_itemList.at(i));
    editor->setEditable(m_isEdit);

    return editor;
}

void QWComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString str = index.model()->data(index, Qt::EditRole).toString();

    QComboBox *comboBox = static_cast<QComboBox *>(editor);
    comboBox->setCurrentText(str);
}

void QWComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox *>(editor);
    QString str = comboBox->currentText();
    model->setData(index, str, Qt::EditRole);
}

void QWComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
