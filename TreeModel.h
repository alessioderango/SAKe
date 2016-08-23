#ifndef TREEMODEL_HPP
#define TREEMODEL_HPP

#include <QStandardItemModel>
#include <iostream>
#include <QtXml>
class TreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit TreeModel(QObject *parent = 0);
    virtual ~TreeModel(){};

    enum TreeModel_Roles
    {
        TreeModel_Role_Name = Qt::DisplayRole,
        TreeModel_Role_Description = Qt::WhatsThisRole,
        TreeModel_Role_Type = Qt::ToolTipRole
    };

    QHash<int, QByteArray> roleNames() const override;
    void addEntry(const QString name, const QString& type, QString description,TreeModel * treeview );


private:
    QStandardItem* getBranch( const QString& branchName,TreeModel * treeview );
    QHash<int, QByteArray> m_roleNameMapping;
    TreeModel* trueModel;

};



#endif // TREEMODEL_HPP
