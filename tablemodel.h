#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QStandardItemModel>
#include <iostream>

class TableModel : public QStandardItemModel
{
     Q_OBJECT
public:
    explicit TableModel(QObject *parent = 0);
    virtual ~TableModel(){};

    enum TableModel_Roles
    {
        TableModel_Role_Name = Qt::DisplayRole,
        TableModel_Role_Description = Qt::WhatsThisRole
    };

     QHash<int, QByteArray> roleNames() const override;

private:
     QHash<int, QByteArray> m_roleNameMapping;

};

#endif // TABLEMODEL_H
