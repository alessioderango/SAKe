#include "xmlmanager.h"

XMLManager::XMLManager()
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

}


int findAllElementsByProject(QString xmlFilePath){

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
        qDebug() << a.at(i).nodeValue();
    }

    // Load document
    return 0;
}

void findElementsWithText(const QDomElement& elem, const QString& attr, QList<QDomElement> &foundElements)
{
   qDebug() <<  elem.text() << " vs " << attr;
   qDebug() <<  elem.nodeName() << " vs " << attr;
   qDebug() <<  elem.nodeType() << " vs " << attr;
   qDebug() <<  QString::compare(elem.text(), attr, Qt::CaseInsensitive);


  if( QString::compare(elem.text(), attr, Qt::CaseInsensitive) == 0 )
    foundElements.append(elem);

  QDomElement child = elem.firstChildElement();
  while( !child.isNull() ) {
    findElementsWithText(child, attr, foundElements);
    child = child.nextSiblingElement();
  }
}

int XMLManager::findProjectName(QString nameProject){

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
    QList<QDomElement> foundElements;
    // Load document
    findAllElementsByProject(xmlFilePath);

    //findElementsWithText(documentElement,nameProject, foundElements);
    qDebug()<< "Receive " <<nameProject;
    qDebug()<< "Receive " <<foundElements.length();
    if(foundElements.length() ==0){
        return 0;
    }else
    {
        if(foundElements.length() ==1){
            return 1;
        }
    }
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



void XMLManager::ReadMainXML(QVariantList &a)
{
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

}
