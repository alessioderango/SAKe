#include "TreeModel.h"

TreeModel::TreeModel(QObject *parent) :
    QStandardItemModel(parent)
{

    m_roleNameMapping[TreeModel_Role_Name] = "name_role";
    m_roleNameMapping[TreeModel_Role_Description] = "description_role";


//    addEntry( "Option E", "Calibration", "This is Option E",this );
//    addEntry( "Option F", "Calibration", "This is Option F" );
//    addEntry( "Option G", "Calibration", "This is Option G" );
//    addEntry( "Option H", "Calibration", "This is Option H" );

//    addEntry( "Option A", "Validation", "This is Option A" );
//    addEntry( "Option B", "Validation", "This is Option B" );
//    addEntry( "Option C", "Validation", "This is Option C" );
//    addEntry( "Option D", "Validation", "This is Option D" );

//    addEntry( "Option A", "Regression", "This is Option A" );
//    addEntry( "Option B", "Regression", "This is Option B" );
//    addEntry( "Option C", "Regression", "This is Option C" );
//    addEntry( "Option D", "Regression", "This is Option D" );
}

void TreeModel::addEntry( const QString name,const QString& type, QString description,TreeModel * treeview )
{

    auto childEntry = new QStandardItem( name );
    childEntry->setData( description, TreeModel_Role_Description );
    //childEntry->parent();
    QStandardItem* entry = getBranch( type,treeview );
    entry->appendRow( childEntry );
    //Get Parent
    //std::cout << "Father "<< childEntry->parent()->text().toStdString() << std::endl;
}

QStandardItem *TreeModel::getBranch(const QString &branchName, TreeModel * treeview)
{
    QStandardItem* entry;
    auto entries = treeview->findItems( branchName );
    if ( entries.count() > 0 )
    {
        entry = entries.at(0);
    }
    else
    {
        entry = new QStandardItem( branchName );
        treeview->appendRow( entry );
    }
    return entry;
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
    return m_roleNameMapping;
}

