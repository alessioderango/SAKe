#include "tablemodel.h"

TableModel::TableModel(QObject *parent) :
    QStandardItemModel(1,9,parent)
{

    std::cout << "Entrato" << std::endl;
    m_roleNameMapping[TableModel_Role_Name] = "name_role";
    m_roleNameMapping[TableModel_Role_Description] = "description_role";
    for(int row = 0; row < 1; row++)
        {
            for(int col = 0; col < 2; col++)
            {
                QModelIndex index
                        = this->index(row,col,QModelIndex());
                // 0 for all data
                this->setData(index,0);
            }
        }

}

QHash<int, QByteArray> TableModel::roleNames() const
{
    return m_roleNameMapping;
}
