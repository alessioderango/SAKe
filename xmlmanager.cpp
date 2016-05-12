#include "xmlmanager.h"

XMLManager::XMLManager(QObject *_listProjects)
{

#ifdef __arm__ //on the target
    xmlFilePath = QString(QDir::currentPath()+"/workspace/main.xml");
    qDebug() << xmlFilePath << endl;
#else
#ifdef __WIN32 //for those developing on windows
    xmlFilePath = QString(QDir::currentPath()+"/workspace/main.xml");
    qDebug() << xmlFilePath << endl;
#else //for those developing on linux
    xmlFilePath = QString(QDir::currentPath()+"/workspace/main.xml");
    qDebug() << xmlFilePath << endl;
#endif
#endif

    listProjects=_listProjects;

}


int findAllElementsByProject(QString xmlFilePath,QString nameProject){

    QFile* filetmp = new QFile(xmlFilePath);
    if( !filetmp->exists()){
        filetmp->open(QIODevice::ReadWrite);
        QTextStream stream( filetmp );
        stream << "<?xml version='1.0' encoding='UTF-8'?>"<< endl;
        stream <<  "<Projects>" << endl;
        stream <<  "</Projects>" << endl;
        filetmp->close();

    }
    delete filetmp;
    QFile inFile( xmlFilePath );


    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for reading." );
        return 0;
    }

    QDomDocument document;
    if( !document.setContent( &inFile ) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        inFile.close();
        return 0;
    }

    inFile.close();

    QDomElement documentElement = document.documentElement();
    QDomNodeList a = documentElement.elementsByTagName("Projects");
    qDebug() << a.length();
    for (int i = 0; i < a.length(); i++) {
        qDebug() << a.at(i).childNodes().at(0).firstChild().nodeValue();
        if(QString::compare(a.at(i).childNodes().at(0).firstChild().nodeValue(), nameProject, Qt::CaseInsensitive)==0)
            return 1;
    }
    // Load document
    return 0;
}

QVariantList XMLManager::getAllElementsFromProjectName(QString nameProject){
    QVariantList list;
    // QString typeProject="CalibrationProject";
    QFile* filetmp = new QFile(xmlFilePath);
    if( !filetmp->exists()){
        filetmp->open(QIODevice::ReadWrite);
        QTextStream stream( filetmp );
        stream << "<?xml version='1.0' encoding='UTF-8'?>"<< endl;
        stream <<  "<Projects>" << endl;
        stream <<  "</Projects>" << endl;
        filetmp->close();

    }
    QFile inFile( xmlFilePath );

    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for reading." );
        return list;
    }

    QDomDocument document;
    if( !document.setContent( &inFile ) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        inFile.close();
        return list;
    }

    inFile.close();

    QDomElement documentElement = document.documentElement();
    QDomNodeList a = documentElement.elementsByTagName("ID");
    QString typeProject;
    qDebug() << a.length();
    for (int i = 0; i < a.length(); i++) {
        qDebug() << a.at(i).firstChild().nodeValue();
        qDebug() << a.at(i).parentNode().nodeName();
        if(QString::compare(a.at(i).firstChild().nodeValue(), nameProject, Qt::CaseInsensitive)==0){
            typeProject = a.at(i).parentNode().nodeName();
            for (int j = 0; j <a.at(i).parentNode().childNodes().length()-1; j++) {
                if(QString::compare(a.at(i).parentNode().nodeName(), "ValidationProject", Qt::CaseInsensitive)==0)
                {
                    list.append(a.at(i).parentNode().childNodes().at(j).firstChild().nodeValue());
                    qDebug() << "parametri" <<a.at(i).parentNode().childNodes().at(j).firstChild().nodeValue();
                }else
                    if(j==1)
                    {
                        list.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(0).firstChild().nodeValue());
                        list.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(1).firstChild().nodeValue());
                        list.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(2).firstChild().nodeValue());
                        qDebug() << "parametri" << a.at(i).parentNode().childNodes().at(j).childNodes().at(0).firstChild().nodeValue();
                        qDebug() << "parametri" <<a.at(i).parentNode().childNodes().at(j).childNodes().at(1).firstChild().nodeValue();
                        qDebug() << "parametri" <<a.at(i).parentNode().childNodes().at(j).childNodes().at(2).firstChild().nodeValue();
                    }else{
                        list.append(a.at(i).parentNode().childNodes().at(j).firstChild().nodeValue());
                        qDebug() << "parametri" <<a.at(i).parentNode().childNodes().at(j).firstChild().nodeValue();
                    }

            }
        }


    }
    list.append(typeProject);
    return list;
}

TreeModel *XMLManager::getTreeview()
{
    return treeview;
}

void XMLManager::setTreeview(TreeModel *value)
{
    treeview = value;
}



int XMLManager::findProjectName(QString nameProject){
    int result = findAllElementsByProject(xmlFilePath,nameProject);
    qDebug() << result << endl;
    return result;
}

int XMLManager::SaveXMLFileAlreadyExistCalibrationProject(QString name,
                                                          QString selection,
                                                          QString value1,
                                                          QString value2,
                                                          QString numberProcessor,
                                                          QString populationSize,
                                                          QString maximumNumberOfGenerations,
                                                          QString tbMax,
                                                          QString tbMin,
                                                          QString dHpMax,
                                                          QString dHpMin,
                                                          QString probabilityOfCrossover,
                                                          QString probabilityOfMutation,
                                                          QString pme,
                                                          QString pmb,
                                                          QString pattern,
                                                          QString pathRains,
                                                          QString pathActivations
                                                          )
{

    QFile inFile( xmlFilePath );
    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for reading." );
        return 0;
    }

    QDomDocument document;
    if( !document.setContent( &inFile ) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        inFile.close();
        return 0;
    }

    inFile.close();

    QDomElement documentElement = document.documentElement();
    QDomNodeList a = documentElement.elementsByTagName("CalibrationProject");
    qDebug() << a.length();
    for (int i = 0; i < a.length(); i++) {
        qDebug() << a.at(i).childNodes().at(0).firstChild().nodeValue();
        qDebug() << name;
        qDebug() << QString::compare(a.at(i).childNodes().at(0).firstChild().nodeValue(), name, Qt::CaseInsensitive);
        int result = QString::compare(a.at(i).childNodes().at(0).firstChild().nodeValue(), name, Qt::CaseInsensitive);
        if(result==0){
            a.at(i).childNodes().at(1).childNodes().at(0).firstChild().setNodeValue(selection);
            a.at(i).childNodes().at(1).childNodes().at(1).firstChild().setNodeValue(value1);
            a.at(i).childNodes().at(1).childNodes().at(2).firstChild().setNodeValue(value2);

            a.at(i).childNodes().at(2).firstChild().setNodeValue(numberProcessor);
            a.at(i).childNodes().at(3).firstChild().setNodeValue(populationSize);
            a.at(i).childNodes().at(4).firstChild().setNodeValue(maximumNumberOfGenerations);
            a.at(i).childNodes().at(5).firstChild().setNodeValue(tbMax);
            a.at(i).childNodes().at(6).firstChild().setNodeValue(tbMin);
            a.at(i).childNodes().at(7).firstChild().setNodeValue(dHpMax);
            a.at(i).childNodes().at(8).firstChild().setNodeValue(dHpMin);
            a.at(i).childNodes().at(9).firstChild().setNodeValue(probabilityOfCrossover);
            a.at(i).childNodes().at(10).firstChild().setNodeValue(probabilityOfMutation);
            a.at(i).childNodes().at(11).firstChild().setNodeValue(pme);
            a.at(i).childNodes().at(12).firstChild().setNodeValue(pmb);
            a.at(i).childNodes().at(13).firstChild().setNodeValue(pattern);
            a.at(i).childNodes().at(14).firstChild().setNodeValue(pathRains);
            a.at(i).childNodes().at(15).firstChild().setNodeValue(pathActivations);
        }

    }

    // Save content back to the file
    if (!inFile.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        qDebug("Basically, now we lost content of a file");
        return 0;
    }
    QByteArray xml = document.toByteArray();
    inFile.write(xml);
    inFile.close();


    return 1;
}

int XMLManager::SaveXMLFileCalibrationProject(QString name,
                                              QString selection,
                                              QString value1,
                                              QString value2,
                                              QString numberProcessor,
                                              QString populationSize,
                                              QString maximumNumberOfGenerations,
                                              QString tbMax,
                                              QString tbMin,
                                              QString dHpMax,
                                              QString dHpMin,
                                              QString probabilityOfCrossover,
                                              QString probabilityOfMutation,
                                              QString pme,
                                              QString pmb,
                                              QString pattern,
                                              QString pathRains,
                                              QString pathActivations
                                              )
{

    //Controllare se esiste un altro progetto con lo stesso nome

    QString filename = QString(xmlFilePath);
    QFile* filetmp = new QFile(xmlFilePath);
    if( !filetmp->exists()){
        filetmp->open(QIODevice::ReadWrite);
        QTextStream stream( filetmp );
        stream << "<?xml version='1.0' encoding='UTF-8'?>"<< endl;
        stream <<  "<Projects>" << endl;
        stream <<  "<NumberProject>0</NumberProject>" << endl;
        stream <<  "</Projects>" << endl;
        filetmp->close();

    }
    delete filetmp;

    QFile inFile( filename );
    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for reading." );
        return 0;
    }



    QDomDocument document;
    if( !document.setContent( &inFile ) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        inFile.close();
        return 0;
    }

    inFile.close();
    qDebug() << "NumProjects = "<<document.childNodes().at(1).childNodes().at(0).firstChild().nodeValue();
    QString numProject = document.childNodes().at(1).childNodes().at(0).firstChild().nodeValue();
    int numProjectInt= numProject.toInt();
    QDomElement documentElement = document.documentElement();

    // create Elements
    QDomElement project = document.createElement( "CalibrationProject" );
    QDomElement id = document.createElement( "ID" );
    QDomElement nameElement = document.createElement( "Name" );
    QDomElement numberProcessorElement = document.createElement( "NumberProcessor" );
    QDomElement populationSizeElement = document.createElement( "PopulationSize" );
    QDomElement maximumNumberOfGenerationsElement = document.createElement( "MaximumNumberOfGenerations" );
    QDomElement tbMaxElement = document.createElement( "tbMax" );
    QDomElement tbMinElement = document.createElement( "tbMin" );
    QDomElement dHpMaxElement = document.createElement( "dHpMax" );
    QDomElement dHpMinElement = document.createElement( "dHpMin" );
    QDomElement probabilityOfCrossoverElement = document.createElement( "ProbabilityOfCrossover" );
    QDomElement probabilityOfMutationElement = document.createElement( "ProbabilityOfMutation" );
    QDomElement pmeElement = document.createElement( "Pme" );
    QDomElement pmbElement = document.createElement( "Pmb" );
    QDomElement patternElement = document.createElement( "Pattern" );
    QDomElement pathRainsElement = document.createElement( "PathRains" );
    QDomElement pathActivationsElement = document.createElement( "PathActivations" );
    QDomText nameText = document.createTextNode(name);
    nameElement.appendChild(nameText);
    QDomElement selectionElement = document.createElement( "Selection" );
    QDomElement typeElement = document.createElement( "Type" );
    QDomElement value1Element = document.createElement( "value1" );
    QDomElement value2Element = document.createElement( "value2" );

    //create TextElement
    QDomText typeText = document.createTextNode( selection );
    QDomText value1Text = document.createTextNode( value1 );
    QDomText value2Text = document.createTextNode( value2 );
    QDomText numberProcessorText = document.createTextNode( numberProcessor );
    QDomText populationSizeText = document.createTextNode( populationSize);
    QDomText maximumNumberOfGenerationsText = document.createTextNode( maximumNumberOfGenerations );
    QDomText tbMaxText = document.createTextNode( tbMax );
    QDomText tbMinText = document.createTextNode( tbMin );
    QDomText dHpMaxText = document.createTextNode( dHpMax );
    QDomText dHpMinText = document.createTextNode( dHpMin );
    QDomText probabilityOfCrossoverText = document.createTextNode( probabilityOfCrossover );
    QDomText probabilityOfMutationText = document.createTextNode( probabilityOfMutation );
    QDomText pmeText = document.createTextNode( pme );
    QDomText pmbText = document.createTextNode( pmb );
    QDomText patternText = document.createTextNode( pattern );
    QDomText pathRainsText = document.createTextNode( pathRains );
    QDomText pathActivationsText = document.createTextNode( pathActivations );
    numProjectInt++;
    QDomText idText = document.createTextNode( QString("%1").arg(numProjectInt));
    document.childNodes().at(1).childNodes().at(0).firstChild().setNodeValue(QString("%1").arg(numProjectInt));

    typeElement.appendChild(typeText);
    value1Element.appendChild(value1Text);
    value2Element.appendChild(value2Text);

    selectionElement.appendChild(typeElement);
    selectionElement.appendChild(value1Element);
    selectionElement.appendChild(value2Element);

    project.appendChild(nameElement);
    project.appendChild(selectionElement);

    numberProcessorElement.appendChild(numberProcessorText);
    project.appendChild(numberProcessorElement);

    populationSizeElement.appendChild(populationSizeText);
    project.appendChild(populationSizeElement);

    maximumNumberOfGenerationsElement.appendChild(maximumNumberOfGenerationsText);
    project.appendChild(maximumNumberOfGenerationsElement);

    tbMaxElement.appendChild(tbMaxText);
    project.appendChild(tbMaxElement);

    tbMinElement.appendChild(tbMinText);
    project.appendChild(tbMinElement);

    dHpMaxElement.appendChild(dHpMaxText);
    project.appendChild(dHpMaxElement);

    dHpMinElement.appendChild(dHpMinText);
    project.appendChild(dHpMinElement);

    probabilityOfCrossoverElement.appendChild(probabilityOfCrossoverText);
    project.appendChild(probabilityOfCrossoverElement);

    probabilityOfMutationElement.appendChild(probabilityOfMutationText);
    project.appendChild(probabilityOfMutationElement);

    pmeElement.appendChild(pmeText);
    project.appendChild(pmeElement);

    pmbElement.appendChild(pmbText);
    project.appendChild(pmbElement);

    patternElement.appendChild(patternText);
    project.appendChild(patternElement);

    pathRainsElement.appendChild(pathRainsText);
    project.appendChild(pathRainsElement);

    pathActivationsElement.appendChild(pathActivationsText);
    project.appendChild(pathActivationsElement);

    id.appendChild(idText);
    project.appendChild(id);

    documentElement.appendChild(project);

    // Save content back to the file
    if (!inFile.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        qDebug("Basically, now we lost content of a file");
        return 0;
    }
    QByteArray xml = document.toByteArray();
    inFile.write(xml);
    inFile.close();

    ReadCalibrationProjectXML();

    return 1;

}

void parseProject(QXmlStreamReader& xml,QVariantList &a,TreeModel* treeview){
    //check to ensure that we were called in the appropriate spot!
    if(xml.tokenType() != QXmlStreamReader::StartElement
            && xml.name() != "CalibrationProject"){
        qDebug() << "Called XML parseQuestionElement "
                 << "without a question Element in the XML stream!";
        return;
    }

    //input "CalibrationProject"


    qDebug() << "Name projects " << xml.name()<< endl;
    while(!(xml.tokenType() == QXmlStreamReader::EndElement
            && xml.name() == "CalibrationProject")){
        //at the start of an element, otherwise ignore and
        //keep reading.
        qDebug() << "Name projects " << xml.name()<< endl;
        if(xml.tokenType() == QXmlStreamReader::StartElement){
            //If the element is a text element, save it
            if(xml.name() == "Name"){
                xml.readNext();
                QString name = xml.text().toString();
                QString id ;
                while(!(xml.tokenType() == QXmlStreamReader::EndElement
                        && xml.name() == "ID")){
                    if(xml.name() == "ID"){
                        xml.readNext();
                        id =  xml.text().toString();
                        break;
                    }
                    qDebug() << "ID " << xml.name()<< endl;
                    xml.readNext();
                }
                qDebug() << "Name projects " << name<< endl;
                qDebug() << "id projects " << id<< endl;
                //a.append(QVariant(xml.text().toString()));
                treeview->addEntry(name,"Calibration",id,treeview);
            }


        }
        //we’re currently looking at some element feld,
        //so read the next element header!
        xml.readNext();
    }//while

    //done!
    return;
}



void XMLManager::ReadCalibrationProjectXML()
{
    treeview->clear();
    QVariant returnedValue;
    QVariantList a;
    qDebug() << "ReadMainXML ";
    QFile* filetmp = new QFile(xmlFilePath);
    if( !filetmp->exists()){
        filetmp->open(QIODevice::ReadWrite);
        QTextStream stream( filetmp );
        stream << "<?xml version='1.0' encoding='UTF-8'?>"<< endl;
        stream <<  "<Projects>" << endl;
        stream <<  "<NumberProject>0</NumberProject>" << endl;
        stream <<  "</Projects>" << endl;
        filetmp->close();

    }

    QString filename = QString(xmlFilePath);
    QFile inFile( filename );
    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for reading." );
        //return 0;
    }

    QDomDocument document;
    if( !document.setContent( &inFile ) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        inFile.close();
        //return 0;
    }
    QDomElement documentElement = document.documentElement();

    QDomNodeList calibrationProject = documentElement.elementsByTagName("CalibrationProject");

     for (int i = 0; i < calibrationProject.length(); i++) {

         treeview->addEntry(calibrationProject.at(i).childNodes().at(0).firstChild().nodeValue(),"Calibration",calibrationProject.at(i).childNodes().at(calibrationProject.at(i).childNodes().length()-1).firstChild().nodeValue(), treeview);
     }

    QDomNodeList validationProject = documentElement.elementsByTagName("ValidationProject");

    for (int i = 0; i < validationProject.length(); i++) {

        treeview->addEntry(validationProject.at(i).childNodes().at(0).firstChild().nodeValue(),"Validation",validationProject.at(i).childNodes().at(validationProject.at(i).childNodes().length()-1).firstChild().nodeValue(), treeview);
    }

    QDomNodeList regressionProject = documentElement.elementsByTagName("RegressionProject");

    for (int i = 0; i < regressionProject.length(); i++) {

        treeview->addEntry(regressionProject.at(i).childNodes().at(0).firstChild().nodeValue(),"Regression",regressionProject.at(i).childNodes().at(regressionProject.at(i).childNodes().length()-1).firstChild().nodeValue(), treeview);
    }

    //    QFile* file = new QFile(xmlFilePath);
    //    if(!file->open(QIODevice::ReadOnly | QIODevice::Text)){
    //        qDebug() << "File not prensent ";
    //        return;
    //    }
    //    QXmlStreamReader xml(file);
    //    while(!xml.atEnd() && !xml.hasError()){

    //        QXmlStreamReader::TokenType token = xml.readNext();

    //        if(token == QXmlStreamReader::StartDocument){
    //            continue;
    //        }

    //        if(token == QXmlStreamReader::StartElement) {

    //            if(xml.name() == "CalibrationProject") {
    //                parseProject(xml,a,treeview);
    //            }
    //        }//startElement
    //    }//while


    //QMetaObject::invokeMethod(listProjects, "addElementList", Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, QVariant::fromValue(a)));

}



int XMLManager::SaveXMLFileValidationProject(const QString &_projectName,
                                             const QString &filenameRainPath,
                                             const QString &filenameActivationPath,
                                             const QString &filenameKernelPath,
                                             const QString &_folderSave){
    QString filename = QString(xmlFilePath);
    QFile* filetmp = new QFile(xmlFilePath);
    if( !filetmp->exists()){
        filetmp->open(QIODevice::ReadWrite);
        QTextStream stream( filetmp );
        stream << "<?xml version='1.0' encoding='UTF-8'?>"<< endl;
        stream <<  "<Projects>" << endl;
        stream <<  "<NumberProject>0</NumberProject>" << endl;
        stream <<  "</Projects>" << endl;
        filetmp->close();

    }
    delete filetmp;
    QFile inFile( filename );
    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for reading." );
        return 0;
    }

    QDomDocument document;
    if( !document.setContent( &inFile ) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        inFile.close();
        return 0;
    }

    inFile.close();
    qDebug() << "NumProjects = "<<document.childNodes().at(1).childNodes().at(0).firstChild().nodeValue();
    QString numProject = document.childNodes().at(1).childNodes().at(0).firstChild().nodeValue();
    int numProjectInt= numProject.toInt();
    QDomElement documentElement = document.documentElement();

    // create Elements
    QDomElement project = document.createElement( "ValidationProject" );
    QDomElement id = document.createElement( "ID" );
    QDomText idText = document.createTextNode( QString("%1").arg(numProjectInt));
    document.childNodes().at(1).childNodes().at(0).firstChild().setNodeValue(QString("%1").arg(numProjectInt));
    QDomElement nameElement = document.createElement( "Name" );
    QDomElement fileNameRainPath = document.createElement( "FileNameRainPath" );
    QDomElement fileNameActivationPath = document.createElement( "FileNameActivationPath" );
    QDomElement fileNameKernelPath = document.createElement( "FileNameKernelPath" );
    QDomElement folderSave = document.createElement( "FolderSave" );


    //create TextElement
    QDomText nameText = document.createTextNode(_projectName);
    QDomText filenameRainPathText = document.createTextNode( filenameRainPath );
    QDomText filenameActivationPathText = document.createTextNode( filenameActivationPath );
    QDomText filenameKernelPathText = document.createTextNode( filenameKernelPath );
    QDomText folderSaveText = document.createTextNode( _folderSave );
    numProjectInt++;

    nameElement.appendChild(nameText);
    fileNameRainPath.appendChild(filenameRainPathText);
    fileNameActivationPath.appendChild(filenameActivationPathText);
    fileNameKernelPath.appendChild(filenameKernelPathText);
    folderSave.appendChild(folderSaveText);


    project.appendChild(nameElement);
    project.appendChild(fileNameRainPath);
    project.appendChild(fileNameActivationPath);
    project.appendChild(fileNameKernelPath);
    project.appendChild(folderSave);
    id.appendChild(idText);
    project.appendChild(id);

    documentElement.appendChild(project);

    // Save content back to the file
    if (!inFile.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        qDebug("Basically, now we lost content of a file");
        return 0;
    }
    QByteArray xml = document.toByteArray();
    inFile.write(xml);
    inFile.close();

    ReadCalibrationProjectXML();

    return 1;
}

int XMLManager::SaveXMLFileAlreadyExistValidationProject(const QString &name,
                                                         const QString &filenameRainPath,
                                                         const QString &filenameActivaionPath,
                                                         const QString &filenameKernelPath,
                                                         const QString &folderSave){
    QFile inFile( xmlFilePath );
    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for reading." );
        return 0;
    }

    QDomDocument document;
    if( !document.setContent( &inFile ) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        inFile.close();
        return 0;
    }

    inFile.close();
    return 0;
    QDomElement documentElement = document.documentElement();
    QDomNodeList a = documentElement.elementsByTagName("ValidationProject");
    qDebug() << a.length();
    for (int i = 0; i < a.length(); i++) {
        qDebug() << a.at(i).childNodes().at(0).firstChild().nodeValue();
        qDebug() << name;
        qDebug() << QString::compare(a.at(i).childNodes().at(0).firstChild().nodeValue(), name, Qt::CaseInsensitive);
        int result = QString::compare(a.at(i).childNodes().at(0).firstChild().nodeValue(), name, Qt::CaseInsensitive);
        if(result==0){
            a.at(i).childNodes().at(1).firstChild().setNodeValue(filenameRainPath);
            a.at(i).childNodes().at(2).firstChild().setNodeValue(filenameActivaionPath);
            a.at(i).childNodes().at(3).firstChild().setNodeValue(filenameKernelPath);
            a.at(i).childNodes().at(4).firstChild().setNodeValue(folderSave);
        }

    }

    // Save content back to the file
    if (!inFile.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        qDebug("Basically, now we lost content of a file");
        return 0;
    }
    QByteArray xml = document.toByteArray();
    inFile.write(xml);
    inFile.close();


    return 1;
}

int XMLManager::SaveXMLFileRegressionProject( const QString &_projectName,
                                              const QString &selection,
                                              const QString &value1,
                                              const QString &value2,
                                              const QString &populationSize,
                                              const QString &percentageCrossover,
                                              const QString &percentageMutation,
                                              const  QString &_percentageWeight,
                                              const  QString &numberProcessor,
                                              const  QString &_numberGamma,
                                              const  QString& _percentageGammaA,
                                              const  QString &_percentageGammaB,
                                              const  QString &_numberLinear,
                                              const  QString& _percentageLinearA,
                                              const  QString &_percentageLinearB,
                                              const  QString &maxGeneration,
                                              const  QString &_fileKernel){
    QString filename = QString(xmlFilePath);
    QFile* filetmp = new QFile(xmlFilePath);
    if( !filetmp->exists()){
        filetmp->open(QIODevice::ReadWrite);
        QTextStream stream( filetmp );
        stream << "<?xml version='1.0' encoding='UTF-8'?>"<< endl;
        stream <<  "<Projects>" << endl;
        stream <<  "<NumberProject>0</NumberProject>" << endl;
        stream <<  "</Projects>" << endl;
        filetmp->close();

    }
    delete filetmp;
    QFile inFile( filename );
    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for reading." );
        return 0;
    }

    QDomDocument document;
    if( !document.setContent( &inFile ) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        inFile.close();
        return 0;
    }

    qDebug() << "NumProjects = "<<document.childNodes().at(1).childNodes().at(0).firstChild().nodeValue();
    QString numProject = document.childNodes().at(1).childNodes().at(0).firstChild().nodeValue();
    int numProjectInt= numProject.toInt();
    inFile.close();

    QDomElement documentElement = document.documentElement();

    // create Elements
    QDomElement project = document.createElement( "RegressionProject" );
    QDomElement nameElement = document.createElement( "Name" );
    QDomElement selectionElement = document.createElement( "Selection" );
    QDomElement typeElement = document.createElement( "Type" );
    QDomElement value1Element = document.createElement( "value1" );
    QDomElement value2Element = document.createElement( "value2" );
    QDomElement populationSizeElement = document.createElement( "PopulationSize" );
    QDomElement probabilityOfCrossoverElement = document.createElement( "ProbabilityOfCrossover" );
    QDomElement probabilityOfMutationElement = document.createElement( "ProbabilityOfMutation" );
    QDomElement percentageWeightElement = document.createElement( "PercentageWeight" );
    QDomElement numberProcessorElement = document.createElement( "NumberProcessor" );
    QDomElement numberGamma = document.createElement( "NumberGamma" );
    QDomElement percentageGammaA = document.createElement( "PercentageGammaA" );
    QDomElement percentageGammaB = document.createElement( "PercentageGammaB" );
    QDomElement numberLinear = document.createElement( "NumberLinear" );
    QDomElement percentageLinearA = document.createElement( "PercentageLinearA" );
    QDomElement percentageLinearB = document.createElement( "PercentageLinearB" );
    QDomElement maximumNumberOfGenerationsElement = document.createElement( "MaximumNumberOfGenerations" );
    QDomElement fileKernel = document.createElement( "FileKernel" );


    //create TextElement
    QDomText nameText = document.createTextNode(_projectName);
    QDomText typeText = document.createTextNode( selection );
    QDomText value1Text = document.createTextNode( value1 );
    QDomText value2Text = document.createTextNode( value2 );
    QDomText populationSizeElementText = document.createTextNode( populationSize );
    QDomText probabilityOfCrossoverElementText = document.createTextNode( percentageCrossover );
    QDomText probabilityOfMutationElementText = document.createTextNode( percentageMutation );
    QDomText percentageWeightText = document.createTextNode( _percentageWeight );
    QDomText numberProcessorElementText = document.createTextNode( numberProcessor );
    QDomText numberGammaText = document.createTextNode( _numberGamma );
    QDomText percentageGammaAText = document.createTextNode( _percentageGammaA );
    QDomText percentageGammaBText = document.createTextNode( _percentageGammaB );
    QDomText numberLinearText = document.createTextNode( _numberLinear );
    QDomText percentageLinearAText = document.createTextNode( _percentageLinearA );
    QDomText percentageLinearBText = document.createTextNode( _percentageLinearB );
    QDomText maximumNumberOfGenerationsElementText = document.createTextNode( maxGeneration );
    QDomText fileKernelText = document.createTextNode( _fileKernel );

    QDomElement id = document.createElement( "ID" );
    numProjectInt++;
    QDomText idText = document.createTextNode( QString("%1").arg(numProjectInt));
    document.childNodes().at(1).childNodes().at(0).firstChild().setNodeValue(QString("%1").arg(numProjectInt));

    nameElement.appendChild(nameText);
    typeElement.appendChild(typeText);
    value1Element.appendChild(value1Text);
    value2Element.appendChild(value2Text);

    selectionElement.appendChild(typeElement);
    selectionElement.appendChild(value1Element);
    selectionElement.appendChild(value2Element);

    project.appendChild(nameElement);
    project.appendChild(selectionElement);

    populationSizeElement.appendChild(populationSizeElementText);
    project.appendChild(populationSizeElement);

    probabilityOfCrossoverElement.appendChild(probabilityOfCrossoverElementText);
    project.appendChild(probabilityOfCrossoverElement);

    probabilityOfMutationElement.appendChild(probabilityOfMutationElementText);
    project.appendChild(probabilityOfMutationElement);

    percentageWeightElement.appendChild(percentageWeightText);
    project.appendChild(percentageWeightElement);

    numberProcessorElement.appendChild(numberProcessorElementText);
    project.appendChild(numberProcessorElement);

    numberGamma.appendChild(numberGammaText);
    project.appendChild(numberGamma);
    percentageGammaA.appendChild(percentageGammaAText);
    project.appendChild(percentageGammaA);
    percentageGammaB.appendChild(percentageGammaBText);
    project.appendChild(percentageGammaB);

    numberLinear.appendChild(numberLinearText);
    project.appendChild(numberLinear);
    percentageLinearA.appendChild(percentageLinearAText);
    project.appendChild(percentageLinearA);
    percentageLinearB.appendChild(percentageLinearBText);
    project.appendChild(percentageLinearB);

    maximumNumberOfGenerationsElement.appendChild(maximumNumberOfGenerationsElementText);
    project.appendChild(maximumNumberOfGenerationsElement);

    fileKernel.appendChild(fileKernelText);
    project.appendChild(fileKernel);
    id.appendChild(idText);
    project.appendChild(id);

    documentElement.appendChild(project);

    // Save content back to the file
    if (!inFile.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        qDebug("Basically, now we lost content of a file");
        return 0;
    }
    QByteArray xml = document.toByteArray();
    inFile.write(xml);
    inFile.close();

    ReadCalibrationProjectXML();

    return 1;
}

int XMLManager::SaveXMLFileAlreadyExistRegressionProject(const QString &name,
                                                         const QString &selection,
                                                         const QString &value1,
                                                         const QString &value2,
                                                         const QString &populationSize,
                                                         const QString &percentageCrossover,
                                                         const QString &percentageMutation,
                                                         const  QString &_percentageWeight,
                                                         const  QString &numberProcessor,
                                                         const  QString &_numberGamma,
                                                         const  QString& _percentageGammaA,
                                                         const  QString &_percentageGammaB,
                                                         const  QString &_numberLinear,
                                                         const  QString& _percentageLinearA,
                                                         const  QString &_percentageLinearB,
                                                         const  QString &maxGeneration,
                                                         const  QString &_fileKernel){
    QFile inFile( xmlFilePath );
    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for reading." );
        return 0;
    }

    QDomDocument document;
    if( !document.setContent( &inFile ) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        inFile.close();
        return 0;
    }

    inFile.close();

    QDomElement documentElement = document.documentElement();
    QDomNodeList a = documentElement.elementsByTagName("RegressionProject");
    qDebug() << a.length();
    for (int i = 0; i < a.length(); i++) {
        qDebug() << a.at(i).childNodes().at(0).firstChild().nodeValue();
        qDebug() << name;
        qDebug() << QString::compare(a.at(i).childNodes().at(0).firstChild().nodeValue(), name, Qt::CaseInsensitive);
        int result = QString::compare(a.at(i).childNodes().at(0).firstChild().nodeValue(), name, Qt::CaseInsensitive);
        if(result==0){
            a.at(i).childNodes().at(1).childNodes().at(0).firstChild().setNodeValue(selection);
            a.at(i).childNodes().at(1).childNodes().at(1).firstChild().setNodeValue(value1);
            a.at(i).childNodes().at(1).childNodes().at(2).firstChild().setNodeValue(value2);

            a.at(i).childNodes().at(2).firstChild().setNodeValue(populationSize);
            a.at(i).childNodes().at(3).firstChild().setNodeValue(percentageCrossover);
            a.at(i).childNodes().at(4).firstChild().setNodeValue(percentageMutation);
            a.at(i).childNodes().at(5).firstChild().setNodeValue(_percentageWeight);
            a.at(i).childNodes().at(6).firstChild().setNodeValue(numberProcessor);
            a.at(i).childNodes().at(7).firstChild().setNodeValue(_numberGamma);
            a.at(i).childNodes().at(8).firstChild().setNodeValue(_percentageGammaA);
            a.at(i).childNodes().at(9).firstChild().setNodeValue(_percentageGammaB);
            a.at(i).childNodes().at(10).firstChild().setNodeValue(_numberLinear);
            a.at(i).childNodes().at(11).firstChild().setNodeValue(_percentageLinearA);
            a.at(i).childNodes().at(12).firstChild().setNodeValue(_percentageLinearB);
            a.at(i).childNodes().at(13).firstChild().setNodeValue(maxGeneration);
            a.at(i).childNodes().at(14).firstChild().setNodeValue(_fileKernel);
        }

    }

    // Save content back to the file
    if (!inFile.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        qDebug("Basically, now we lost content of a file");
        return 0;
    }
    QByteArray xml = document.toByteArray();
    inFile.write(xml);
    inFile.close();


    return 1;
}

