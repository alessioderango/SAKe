#include "xmlmanager.h"

XMLManager::XMLManager(QObject *_listProjects)
{

#ifdef __arm__ //on the target
    xmlFilePath("/home/You/QT/YourProject/myXML.xml");
#else
#ifdef __WIN32 //for those developing on windows
    xmlFilePath = QString(QDir::currentPath()+"/main.xml");
    qDebug() << xmlFilePath << endl;
#else //for those developing on linux
    xmlFilePath("/home/You/QT/YourProject/myXML.xml");
#endif
#endif

    listProjects=_listProjects;

}


int findAllElementsByProject(QString xmlFilePath,QString nameProject){

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
    QDomNodeList a = documentElement.elementsByTagName("Project");
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
    QDomNodeList a = documentElement.elementsByTagName("Project");
    qDebug() << a.length();
    for (int i = 0; i < a.length(); i++) {
        qDebug() << a.at(i).childNodes().at(0).firstChild().nodeValue();
        if(QString::compare(a.at(i).childNodes().at(0).firstChild().nodeValue(), nameProject, Qt::CaseInsensitive)==0)
            for (int j = 0; j < a.at(i).childNodes().length(); j++) {
                if(j==1)
                {
                    list.append(a.at(i).childNodes().at(j).childNodes().at(0).firstChild().nodeValue());
                    list.append(a.at(i).childNodes().at(j).childNodes().at(1).firstChild().nodeValue());
                    list.append(a.at(i).childNodes().at(j).childNodes().at(2).firstChild().nodeValue());
                    qDebug() << a.at(i).childNodes().at(j).childNodes().at(0).firstChild().nodeValue();
                    qDebug() << a.at(i).childNodes().at(j).childNodes().at(1).firstChild().nodeValue();
                    qDebug() << a.at(i).childNodes().at(j).childNodes().at(2).firstChild().nodeValue();
                }else{
                    list.append(a.at(i).childNodes().at(j).firstChild().nodeValue());
                    qDebug() << a.at(i).childNodes().at(j).firstChild().nodeValue();
                }

            }


    }
    return list;
}



int XMLManager::findProjectName(QString nameProject){
    int result = findAllElementsByProject(xmlFilePath,nameProject);
    qDebug() << result << endl;
    return result;
}

int XMLManager::SaveXMLFileAlreadyExist(QString name,
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
    QDomNodeList a = documentElement.elementsByTagName("Project");
    qDebug() << a.length();
    for (int i = 0; i < a.length(); i++) {
        qDebug() << a.at(i).childNodes().at(0).firstChild().nodeValue();
        if(QString::compare(a.at(i).childNodes().at(0).firstChild().nodeValue(), name, Qt::CaseInsensitive)==0)


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

int XMLManager::SaveXMLFile(QString name,
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

    QDomElement documentElement = document.documentElement();

    // create Elements
    QDomElement project = document.createElement( "Project" );
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

    documentElement.appendChild(project);

    // Save content back to the file
    if (!inFile.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        qDebug("Basically, now we lost content of a file");
        return 0;
    }
    QByteArray xml = document.toByteArray();
    inFile.write(xml);
    inFile.close();

    ReadMainXML();

}

void parseProject(QXmlStreamReader& xml,QVariantList &a){
    //check to ensure that we were called in the appropriate spot!
    if(xml.tokenType() != QXmlStreamReader::StartElement
            && xml.name() != "Project"){
        qDebug() << "Called XML parseQuestionElement "
                 << "without a question Element in the XML stream!";
        return;
    }

    while(!(xml.tokenType() == QXmlStreamReader::EndElement
            && xml.name() == "Project")){
        //at the start of an element, otherwise ignore and
        //keep reading.
        if(xml.tokenType() == QXmlStreamReader::StartElement){
            //If the element is a text element, save it
            if(xml.name() == "Name"){
                xml.readNext();
                qDebug() << "Name projects " << xml.text().toString()<< endl;
                a.append(QVariant(xml.text().toString()));
            }


        }
        //we’re currently looking at some element feld,
        //so read the next element header!
        xml.readNext();
    }//while

    //done!
    return;
}



void XMLManager::ReadMainXML()
{
    QVariant returnedValue;
    QVariantList a;
    qDebug() << "ReadMainXML ";
    QFile* file = new QFile(xmlFilePath);
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "File not prensent ";
        return;
    }
    QXmlStreamReader xml(file);
    while(!xml.atEnd() && !xml.hasError()){

        QXmlStreamReader::TokenType token = xml.readNext();

        if(token == QXmlStreamReader::StartDocument){
            continue;
        }

        if(token == QXmlStreamReader::StartElement) {

            if(xml.name() == "Project") {
                parseProject(xml,a);
            }
        }//startElement
    }//while


    QMetaObject::invokeMethod(listProjects, "addElementList", Q_RETURN_ARG(QVariant, returnedValue), Q_ARG(QVariant, QVariant::fromValue(a)));

}
