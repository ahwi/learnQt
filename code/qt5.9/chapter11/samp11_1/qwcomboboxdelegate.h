#ifndef QWCOMBOBOXDELEGATE_H
#define QWCOMBOBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>


class QWComboBoxDelegate : public QStyledItemDelegate
{
public:
    QWComboBoxDelegate();

private:
    QStringList m_itemList;    //选择列表
    bool m_isEdit;    //是否可编辑

public:
    // 初始化设置列表内容、是否可编辑
    void setItems(QStringList items,bool isEdit);

    // 自定义代理组件必须实现下面4个函数
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void  setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void  setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void  updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif // QWCOMBOBOXDELEGATE_H
