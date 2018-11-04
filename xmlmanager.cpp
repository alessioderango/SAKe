#include "xmlmanager.h"

XMLManager::XMLManager()
{

#ifdef __arm__ //on the target

    xmlFilePath = QString(QDir::currentPath()+"/workspace/main.xml");
//    qDebug() << xmlFilePath << endl;
#else
#ifdef __WIN32 //for those developing on windows
    folderPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    QDir dirSAKe(folderPath);
    if (!dirSAKe.exists()){
        dirSAKe.mkdir(".");
    }

    QDir dir(folderPath+"/workspace");
    if (!dir.exists()){
        dir.mkdir(".");
    }
    QDir dirRegression(folderPath+"/workspace/regression");
    if (!dirRegression.exists()){
        dirRegression.mkdir(".");
    }

    QDir dirCalibration(folderPath+"/workspace/calibration");
    if (!dirCalibration.exists()){
        dirCalibration.mkdir(".");
    }

    xmlFilePath = QString(folderPath+"/workspace/main.xml");
//    qDebug() << xmlFilePath << endl;


#else //for those developing on linux
    xmlFilePath = QString(QDir::currentPath()+"/workspace/main.xml");
//    qDebug() << xmlFilePath << endl;
#endif
#endif

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
//    qDebug() << a.length();
    for (int i = 0; i < a.length(); i++) {
//        qDebug() << a.at(i).childNodes().at(0).firstChild().nodeValue();
        if(QString::compare(a.at(i).childNodes().at(0).firstChild().nodeValue(), nameProject, Qt::CaseInsensitive)==0)
            return 1;
    }
    // Load document
    return 0;
}

QVariantList XMLManager::getAllElementsFromProjectName(QString idProject){
    QVariantList matrix;
    QVariantList list;
    QVariantList listGamma1;
    QVariantList listGamma2;
    QVariantList listLinear;

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
        return matrix;
    }

    QDomDocument document;
    if( !document.setContent( &inFile ) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        inFile.close();
        return matrix;
    }

    inFile.close();

    QDomElement documentElement = document.documentElement();
    QDomNodeList a = documentElement.elementsByTagName("ID");
    QString typeProject;
//    qDebug() << a.length();
    for (int i = 0; i < a.length(); i++) {
//        qDebug() << a.at(i).firstChild().nodeValue();
//        qDebug() << a.at(i).parentNode().nodeName();
        if(QString::compare(a.at(i).firstChild().nodeValue(), idProject, Qt::CaseInsensitive)==0){
            typeProject = a.at(i).parentNode().nodeName();
            for (int j = 0; j <a.at(i).parentNode().childNodes().length()-1; j++) {
                if(QString::compare(a.at(i).parentNode().nodeName(), "ValidationProject", Qt::CaseInsensitive)==0)
                {
                    list.append(a.at(i).parentNode().childNodes().at(j).firstChild().nodeValue());
//                    qDebug() << "parametri" <<a.at(i).parentNode().childNodes().at(j).firstChild().nodeValue();
                }else
                    if(QString::compare(a.at(i).parentNode().nodeName(), "RegressionProject", Qt::CaseInsensitive)==0)
                    {
                        //1 Selection Type
                        //2 Selection Parameter 1
                        //3 Selection Parameter 2

                        //4 PopSize
                        //5 numberProcessor
                        //6 Probability crossover
                        //7 Probability mutation
                        //8 Max gen
                        //9 file kernel

                        //10 file kernel
//                        qDebug() << "Name " << a.at(i).parentNode().childNodes().at(j).nodeName() << endl;

                        if(QString::compare(a.at(i).parentNode().childNodes().at(j).nodeName(), "Selection", Qt::CaseInsensitive)==0)
                        {
                            //Selection
                            list.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(0).firstChild().nodeValue());
                            list.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(1).firstChild().nodeValue());
                            list.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(2).firstChild().nodeValue());
//                            qDebug() << "parametri" << a.at(i).parentNode().childNodes().at(j).childNodes().at(0).firstChild().nodeValue();
//                            qDebug() << "parametri" <<a.at(i).parentNode().childNodes().at(j).childNodes().at(1).firstChild().nodeValue();
//                            qDebug() << "parametri" <<a.at(i).parentNode().childNodes().at(j).childNodes().at(2).firstChild().nodeValue();
                        }else
                            if(QString::compare(a.at(i).parentNode().childNodes().at(j).nodeName(), "GammaFunction1", Qt::CaseInsensitive)==0){//j==8){
                                //Gamma1
                                int numberFunctionGamma1 = a.at(i).parentNode().childNodes().at(j).childNodes().at(0).firstChild().nodeValue().toInt();
                                for (int k = 1; k <= numberFunctionGamma1; k++)
                                {
                                    //amax
                                    listGamma1.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(0).firstChild().nodeValue());
                                    //amin
                                    listGamma1.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(1).firstChild().nodeValue());
                                    //bmax
                                    listGamma1.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(2).firstChild().nodeValue());
                                    //bmin
                                    listGamma1.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(3).firstChild().nodeValue());
                                    //wmax
                                    listGamma1.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(4).firstChild().nodeValue());
                                    //wmin
                                    listGamma1.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(5).firstChild().nodeValue());
                                    //pa
                                    listGamma1.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(6).firstChild().nodeValue());
                                    //pb
                                    listGamma1.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(7).firstChild().nodeValue());
                                    //pw
                                    listGamma1.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(8).firstChild().nodeValue());
                                    //tmax
                                    listGamma1.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(9).firstChild().nodeValue());
                                    //tmin
                                    listGamma1.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(10).firstChild().nodeValue());
                                    //pt
                                    listGamma1.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(11).firstChild().nodeValue());

                                }
                            }else
                                if(QString::compare(a.at(i).parentNode().childNodes().at(j).nodeName(), "GammaFunction2", Qt::CaseInsensitive)==0){
                                    //Gamma2
                                    int numberFunctionGamma2 = a.at(i).parentNode().childNodes().at(j).childNodes().at(0).firstChild().nodeValue().toInt();

                                    for (int k = 1; k <= numberFunctionGamma2; k++)
                                    {
                                        //amax
                                        listGamma2.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(0).firstChild().nodeValue());
                                        //amin
                                        listGamma2.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(1).firstChild().nodeValue());
                                        //bmax
                                        listGamma2.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(2).firstChild().nodeValue());
                                        //bmin
                                        listGamma2.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(3).firstChild().nodeValue());
                                        //wmax
                                        listGamma2.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(4).firstChild().nodeValue());
                                        //wmin
                                        listGamma2.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(5).firstChild().nodeValue());
                                        //pa
                                        listGamma2.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(6).firstChild().nodeValue());
                                        //pb
                                        listGamma2.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(7).firstChild().nodeValue());
                                        //pw
                                        listGamma2.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(8).firstChild().nodeValue());

                                        //tmax
                                        listGamma2.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(9).firstChild().nodeValue());
                                        //tmin
                                        listGamma2.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(10).firstChild().nodeValue());
                                        //pt
                                        listGamma2.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(11).firstChild().nodeValue());
                                    }
                                }else
                                    if(QString::compare(a.at(i).parentNode().childNodes().at(j).nodeName(), "LinearFunction", Qt::CaseInsensitive)==0){
                                        //Linear
                                        int numberLinearFunction = a.at(i).parentNode().childNodes().at(j).childNodes().at(0).firstChild().nodeValue().toInt();

                                        for (int k = 1; k <= numberLinearFunction; k++)
                                        {
                                            //amax
                                            listLinear.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(0).firstChild().nodeValue());
                                            //amin
                                            listLinear.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(1).firstChild().nodeValue());
                                            //bmax
                                            listLinear.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(2).firstChild().nodeValue());
                                            //bmin
                                            listLinear.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(3).firstChild().nodeValue());
                                            //wmax
                                            listLinear.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(4).firstChild().nodeValue());
                                            //wmin
                                            listLinear.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(5).firstChild().nodeValue());
                                            //pa
                                            listLinear.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(6).firstChild().nodeValue());
                                            //pb
                                            listLinear.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(7).firstChild().nodeValue());
                                            //pw
                                            listLinear.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(8).firstChild().nodeValue());
                                            //tmax
                                            listLinear.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(9).firstChild().nodeValue());
                                            //tmin
                                            listLinear.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(10).firstChild().nodeValue());
                                            //pt
                                            listLinear.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(k).childNodes().at(11).firstChild().nodeValue());

                                        }
                                    }else{

                                        list.append(a.at(i).parentNode().childNodes().at(j).firstChild().nodeValue());
//                                        qDebug() << "parametri" <<a.at(i).parentNode().childNodes().at(j).firstChild().nodeValue();
                                    }
                    }else
                    {
                        if(QString::compare(a.at(i).parentNode().nodeName(), "CalibrationProject", Qt::CaseInsensitive)==0)
                        {
                            if(j==1)
                            {
                                //Selection
                                list.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(0).firstChild().nodeValue());
                                list.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(1).firstChild().nodeValue());
                                list.append(a.at(i).parentNode().childNodes().at(j).childNodes().at(2).firstChild().nodeValue());
//                                qDebug() << "parametri" << a.at(i).parentNode().childNodes().at(j).childNodes().at(0).firstChild().nodeValue();
//                                qDebug() << "parametri" <<a.at(i).parentNode().childNodes().at(j).childNodes().at(1).firstChild().nodeValue();
//                                qDebug() << "parametri" <<a.at(i).parentNode().childNodes().at(j).childNodes().at(2).firstChild().nodeValue();
                            }else

                            list.append(a.at(i).parentNode().childNodes().at(j).firstChild().nodeValue());
//                            qDebug() << "parametri j == "<<j <<a.at(i).parentNode().childNodes().at(j).firstChild().nodeValue();
                        }
                    }

            }
        }


    }

    matrix.append(list);
    matrix.append("-");
    matrix.append(listGamma1);
    matrix.append("-");
    matrix.append(listGamma2);
    matrix.append("-");
    matrix.append(listLinear);
    matrix.append("-");
    matrix.append(typeProject);

    return matrix;
}

QTreeWidget *XMLManager::getTreeview()
{
    return treeview;
}

void XMLManager::setTreeview(QTreeWidget *value)
{
    treeview = value;
}



int XMLManager::findProjectName(QString nameProject){
    int result = findAllElementsByProject(xmlFilePath,nameProject);
//    qDebug() << result << endl;
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
                                                          QString probabilityOfSelection,
                                                          QString probabilityOfCrossover,
                                                          QString probabilityOfMutation,
                                                          QString pme,
                                                          QString pmb,
                                                          QString pattern,
                                                          QString pathRains,
                                                          QString pathActivations,
                                                          QString typeReplacement,
                                                          QString numberElitist,
                                                          QString seed,
                                                          QString saveKernels,
                                                          QString numberOfKernelToBeSaved,
                                                          std::vector<QString> orders,
                                                          QString typeFitness,
                                                          QString numberOfLines)
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
//    qDebug() << a.length();
//    qDebug() << "SALVO PROGETTO GIà ESISTENTE";
    for (int i = 0; i < a.length(); i++) {
//        qDebug() << a.at(i).childNodes().at(0).firstChild().nodeValue();
//        qDebug() << name;
//        qDebug() << QString::compare(a.at(i).childNodes().at(0).firstChild().nodeValue(), name, Qt::CaseInsensitive);
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
            a.at(i).childNodes().at(9).firstChild().setNodeValue(probabilityOfSelection);
            a.at(i).childNodes().at(10).firstChild().setNodeValue(probabilityOfCrossover);
            a.at(i).childNodes().at(11).firstChild().setNodeValue(probabilityOfMutation);
            a.at(i).childNodes().at(12).firstChild().setNodeValue(pme);
            a.at(i).childNodes().at(13).firstChild().setNodeValue(pmb);
            a.at(i).childNodes().at(14).firstChild().setNodeValue(pattern);
            a.at(i).childNodes().at(15).firstChild().setNodeValue(pathRains);
            a.at(i).childNodes().at(16).firstChild().setNodeValue(pathActivations);
            a.at(i).childNodes().at(17).firstChild().setNodeValue(typeReplacement);
            a.at(i).childNodes().at(18).firstChild().setNodeValue(numberElitist);
            a.at(i).childNodes().at(19).firstChild().setNodeValue(seed);
            a.at(i).childNodes().at(20).firstChild().setNodeValue(saveKernels);
            a.at(i).childNodes().at(21).firstChild().setNodeValue(numberOfKernelToBeSaved);
            a.at(i).childNodes().at(22).firstChild().setNodeValue(orders[0]);
            a.at(i).childNodes().at(23).firstChild().setNodeValue(orders[1]);
            a.at(i).childNodes().at(24).firstChild().setNodeValue(orders[2]);
            a.at(i).childNodes().at(25).firstChild().setNodeValue(orders[3]);
            a.at(i).childNodes().at(26).firstChild().setNodeValue(typeFitness);
            a.at(i).childNodes().at(27).firstChild().setNodeValue(numberOfLines);

        }

    }

//    qDebug() << "\n";
//    qDebug() << "\n";
//    qDebug() << "\n";
//    qDebug() << "AAAAAAAAAAAAAAAAAAAAAAaa\n";

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
                                              QString probabilityOfSelection,
                                              QString probabilityOfCrossover,
                                              QString probabilityOfMutation,
                                              QString pme,
                                              QString pmb,
                                              QString pattern,
                                              QString pathRains,
                                              QString pathActivations,
                                              QString typeReplacement,
                                              QString numberElitist,
                                              QString seed,
                                              QString saveKernels,
                                              QString numberOfKernelToBeSaved,
                                              std::vector<QString> orders,
                                              QString typeFitness,
                                              QString numberOfLines)
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
//    qDebug() << "NumProjects = "<<document.childNodes().at(1).childNodes().at(0).firstChild().nodeValue();
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
    QDomElement probabilityOfSelectionElement = document.createElement( "ProbabilityOfSelection" );
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
    QDomElement typeReplacementDom = document.createElement( "typeReplacement" );
    QDomElement numberElitistDom = document.createElement( "numberElitist" );
    QDomElement seedDom = document.createElement( "seed" );
    QDomElement saveKernelsDom = document.createElement( "saveKernels" );
    QDomElement numberOfKernelToBeSavedDom = document.createElement( "numberOfKernelToBeSaved" );
    QDomElement order0Dom = document.createElement( "order0Dom" );
    QDomElement order1Dom = document.createElement( "order1Dom" );
    QDomElement order2Dom = document.createElement( "order2Dom" );
    QDomElement order3Dom = document.createElement( "order3Dom" );

    QDomElement typeFitnessDOM = document.createElement( "typeFitness" );
    QDomElement numberOfLinesDOM = document.createElement( "numberOfLines" );

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
    QDomText probabilityOfSelectionText = document.createTextNode( probabilityOfSelection );
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

    QDomText typeReplacementText = document.createTextNode( typeReplacement );
    QDomText numberElitistText = document.createTextNode( numberElitist );
    typeReplacementDom.appendChild(typeReplacementText);
    numberElitistDom.appendChild(numberElitistText);

    QDomText seedText = document.createTextNode( seed );
    QDomText saveKernelsText = document.createTextNode( saveKernels );
    QDomText numberOfKernelToBeSavedText = document.createTextNode( numberOfKernelToBeSaved );
    QDomText order0Text = document.createTextNode( orders[0] );
    QDomText order1Text = document.createTextNode( orders[1] );
    QDomText order2Text = document.createTextNode( orders[2] );
    QDomText order3Text = document.createTextNode( orders[3] );
    seedDom.appendChild(seedText);
    saveKernelsDom.appendChild(saveKernelsText);
    numberOfKernelToBeSavedDom.appendChild(numberOfKernelToBeSavedText);
    order0Dom.appendChild(order0Text);
    order1Dom.appendChild(order1Text);
    order2Dom.appendChild(order2Text);
    order3Dom.appendChild(order3Text);

    QDomText typeFitnessText = document.createTextNode(typeFitness);

    typeFitnessDOM.appendChild(typeFitnessText);
    QDomText numberOfLinesText = document.createTextNode(numberOfLines);
    numberOfLinesDOM.appendChild(numberOfLinesText);


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

    probabilityOfSelectionElement.appendChild(probabilityOfSelectionText);
    project.appendChild(probabilityOfSelectionElement);

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

    project.appendChild(typeReplacementDom);
    project.appendChild(numberElitistDom);

    project.appendChild(seedDom);
    project.appendChild(saveKernelsDom);
    project.appendChild(numberOfKernelToBeSavedDom);
    project.appendChild(order0Dom);
    project.appendChild(order1Dom);
    project.appendChild(order2Dom);
    project.appendChild(order3Dom);
    project.appendChild(typeFitnessDOM);
    project.appendChild(numberOfLinesDOM);

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

void parseProject(QXmlStreamReader& xml,QTreeWidget* treeview){
    //check to ensure that we were called in the appropriate spot!
    if(xml.tokenType() != QXmlStreamReader::StartElement
            && xml.name() != "CalibrationProject"){
        qDebug() << "Called XML parseQuestionElement "
                 << "without a question Element in the XML stream!";
        return;
    }

    //input "CalibrationProject"


//    qDebug() << "Name projects " << xml.name()<< endl;
    while(!(xml.tokenType() == QXmlStreamReader::EndElement
            && xml.name() == "CalibrationProject")){
        //at the start of an element, otherwise ignore and
        //keep reading.
//        qDebug() << "Name projects " << xml.name()<< endl;
        if(xml.tokenType() == QXmlStreamReader::StartElement){
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
//                    qDebug() << "ID " << xml.name()<< endl;
                    xml.readNext();
                }
//                qDebug() << "Name projects " << name<< endl;
//                qDebug() << "id projects " << id<< endl;
                //treeview->addEntry(name,"Calibration",id,treeview);
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
//    qDebug() << "ReadMainXML ";
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
    }
    QDomElement documentElement = document.documentElement();

    QDomNodeList calibrationProject = documentElement.elementsByTagName("CalibrationProject");
    QTreeWidgetItem * cali = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Calibration")));
    QTreeWidgetItem * vali = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Validation")));
    QTreeWidgetItem * regre = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Regression")));

    treeview->insertTopLevelItem(0, vali);
    treeview->insertTopLevelItem(0, regre);
    treeview->insertTopLevelItem(0, cali);

    for (int i = 0; i < calibrationProject.length(); i++) {
        QTreeWidgetItem * tmp = new QTreeWidgetItem((QTreeWidget*)0, QStringList(calibrationProject.at(i).childNodes().at(0).firstChild().nodeValue()));
        tmp->setData(0, Qt::UserRole, calibrationProject.at(i).childNodes().at(calibrationProject.at(i).childNodes().length()-1).firstChild().nodeValue());
        cali->addChild(tmp);
     }

    QDomNodeList validationProject = documentElement.elementsByTagName("ValidationProject");
    for (int i = 0; i < validationProject.length(); i++) {
        QTreeWidgetItem * tmp = new QTreeWidgetItem((QTreeWidget*)0, QStringList(validationProject.at(i).childNodes().at(0).firstChild().nodeValue()));
        tmp->setData(0, Qt::UserRole,validationProject.at(i).childNodes().at(validationProject.at(i).childNodes().length()-1).firstChild().nodeValue());
        vali->addChild(tmp);
     }

     QDomNodeList regressionProject = documentElement.elementsByTagName("RegressionProject");

     for (int i = 0; i < regressionProject.length(); i++) {
           QTreeWidgetItem * tmp = new QTreeWidgetItem((QTreeWidget*)0, QStringList(regressionProject.at(i).childNodes().at(0).firstChild().nodeValue()));
           tmp->setData(0, Qt::UserRole,regressionProject.at(i).childNodes().at(regressionProject.at(i).childNodes().length()-1).firstChild().nodeValue());
           regre->addChild(tmp);
     }


}



int XMLManager::SaveXMLFileValidationProject(const QString &_projectName,
                                             const QString &filenameRainPath,
                                             const QString &filenameActivationPath,
                                             const QString &filenameKernelPath,
                                             const QString &_folderSave,
                                             const QString &_numberOfLinesForAUC){
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
//    qDebug() << "NumProjects = "<<document.childNodes().at(1).childNodes().at(0).firstChild().nodeValue();
    QString numProject = document.childNodes().at(1).childNodes().at(0).firstChild().nodeValue();
    int numProjectInt= numProject.toInt();
    QDomElement documentElement = document.documentElement();

    // create Elements
    QDomElement project = document.createElement( "ValidationProject" );
    QDomElement id = document.createElement( "ID" );
    numProjectInt++;
    QDomText idText = document.createTextNode( QString("%1").arg(numProjectInt));
    document.childNodes().at(1).childNodes().at(0).firstChild().setNodeValue(QString("%1").arg(numProjectInt));
    QDomElement nameElement = document.createElement( "Name" );
    QDomElement fileNameRainPath = document.createElement( "FileNameRainPath" );
    QDomElement fileNameActivationPath = document.createElement( "FileNameActivationPath" );
    QDomElement fileNameKernelPath = document.createElement( "FileNameKernelPath" );
    QDomElement folderSave = document.createElement( "FolderSave" );
    QDomElement numberOfLinesForAUCDOM = document.createElement( "numberOfLinesForAUC" );


    //create TextElement
    QDomText nameText = document.createTextNode(_projectName);
    QDomText filenameRainPathText = document.createTextNode( filenameRainPath );
    QDomText filenameActivationPathText = document.createTextNode( filenameActivationPath );
    QDomText filenameKernelPathText = document.createTextNode( filenameKernelPath );
    QDomText folderSaveText = document.createTextNode( _folderSave );
    QDomText numberOfLinesForAUCText = document.createTextNode( _numberOfLinesForAUC );


    nameElement.appendChild(nameText);
    fileNameRainPath.appendChild(filenameRainPathText);
    fileNameActivationPath.appendChild(filenameActivationPathText);
    fileNameKernelPath.appendChild(filenameKernelPathText);
    folderSave.appendChild(folderSaveText);
    numberOfLinesForAUCDOM.appendChild(numberOfLinesForAUCText);


    project.appendChild(nameElement);
    project.appendChild(fileNameRainPath);
    project.appendChild(fileNameActivationPath);
    project.appendChild(fileNameKernelPath);
    project.appendChild(folderSave);
    project.appendChild(numberOfLinesForAUCDOM);
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
                                                         const QString &folderSave,
                                                         const QString &numberOfLinesForAUC){
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
    QDomNodeList a = documentElement.elementsByTagName("ValidationProject");
//    qDebug() << a.length();
    for (int i = 0; i < a.length(); i++) {
//        qDebug() << a.at(i).childNodes().at(0).firstChild().nodeValue();
//        qDebug() << name;
//        qDebug() << QString::compare(a.at(i).childNodes().at(0).firstChild().nodeValue(), name, Qt::CaseInsensitive);
        int result = QString::compare(a.at(i).childNodes().at(0).firstChild().nodeValue(), name, Qt::CaseInsensitive);
        if(result==0){
            a.at(i).childNodes().at(1).firstChild().setNodeValue(filenameRainPath);
            a.at(i).childNodes().at(2).firstChild().setNodeValue(filenameActivaionPath);
            a.at(i).childNodes().at(3).firstChild().setNodeValue(filenameKernelPath);
            a.at(i).childNodes().at(4).firstChild().setNodeValue(folderSave);
            a.at(i).childNodes().at(5).firstChild().setNodeValue(numberOfLinesForAUC);
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

QDomElement XMLManager::getGamma1ElementXML(std::vector<std::vector<double> > matrixGamma1, QDomDocument document)
{
    QDomElement gammaFunction1 =document.createElement( "GammaFunction1" );
    QDomElement numberGammaFunction1 =document.createElement( "Number" );
    numberGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma1.size())));
    gammaFunction1.appendChild(numberGammaFunction1);
    for (size_t i = 0; i < matrixGamma1.size(); i++) {
        QDomElement gammaParameters =document.createElement( "Parameters" );
        QDomElement amaxGammaFunction1 =document.createElement( "amax" );
        amaxGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma1[i][0])));
        gammaParameters.appendChild(amaxGammaFunction1);

        QDomElement aminGammaFunction1 =document.createElement( "amin" );
        aminGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma1[i][1])));
        gammaParameters.appendChild(aminGammaFunction1);

        QDomElement bmaxGammaFunction1 =document.createElement( "bmax" );
        bmaxGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma1[i][2])));
        gammaParameters.appendChild(bmaxGammaFunction1);

        QDomElement bminGammaFunction1 =document.createElement( "bmin" );
        bminGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma1[i][3])));
        gammaParameters.appendChild(bminGammaFunction1);

        QDomElement wmaxGammaFunction1 =document.createElement( "wmax" );
        wmaxGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma1[i][4])));
        gammaParameters.appendChild(wmaxGammaFunction1);

        QDomElement wminGammaFunction1 =document.createElement( "wmin" );
        wminGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma1[i][5])));
        gammaParameters.appendChild(wminGammaFunction1);

        QDomElement paGammaFunction1 =document.createElement( "pa" );
        paGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma1[i][6])));
        gammaParameters.appendChild(paGammaFunction1);

        QDomElement pbGammaFunction1 =document.createElement( "pb" );
        pbGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma1[i][7])));
        gammaParameters.appendChild(pbGammaFunction1);

        QDomElement pwGammaFunction1 =document.createElement( "pw" );
        pwGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma1[i][8])));
        gammaParameters.appendChild(pwGammaFunction1);

        QDomElement maxtransGammaFunction1 =document.createElement( "tmax" );
        maxtransGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma1[i][9])));
        gammaParameters.appendChild(maxtransGammaFunction1);

        QDomElement mintransGammaFunction1 =document.createElement( "tmin" );
        mintransGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma1[i][10])));
        gammaParameters.appendChild(mintransGammaFunction1);

        QDomElement perctransGammaFunction1 =document.createElement( "pt" );
        perctransGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma1[i][11])));
        gammaParameters.appendChild(perctransGammaFunction1);
        gammaFunction1.appendChild(gammaParameters);
    }

    return gammaFunction1;
}

QDomElement XMLManager::getGamma2ElementXML(std::vector<std::vector<double> > matrixGamma2, QDomDocument document)
{
    QDomElement gammaFunction2 =document.createElement( "GammaFunction2" );
    QDomElement numberGammaFunction2 =document.createElement( "Number" );
    numberGammaFunction2.appendChild(document.createTextNode(QString::number(matrixGamma2.size())));
    gammaFunction2.appendChild(numberGammaFunction2);

    for (size_t i = 0; i < matrixGamma2.size(); i++) {
        QDomElement gammaParameters2 =document.createElement( "Parameters" );
        QDomElement amaxGammaFunction2 =document.createElement( "amax" );
        amaxGammaFunction2.appendChild(document.createTextNode(QString::number(matrixGamma2[i][0])));
        gammaParameters2.appendChild(amaxGammaFunction2);

        QDomElement aminGammaFunction2 =document.createElement( "amin" );
        aminGammaFunction2.appendChild(document.createTextNode(QString::number(matrixGamma2[i][1])));
        gammaParameters2.appendChild(aminGammaFunction2);

        QDomElement bmaxGammaFunction2 =document.createElement( "bmax" );
        bmaxGammaFunction2.appendChild(document.createTextNode(QString::number(matrixGamma2[i][2])));
        gammaParameters2.appendChild(bmaxGammaFunction2);

        QDomElement bminGammaFunction2 =document.createElement( "bmin" );
        bminGammaFunction2.appendChild(document.createTextNode(QString::number(matrixGamma2[i][3])));
        gammaParameters2.appendChild(bminGammaFunction2);

        QDomElement wmaxGammaFunction2 =document.createElement( "wmax" );
        wmaxGammaFunction2.appendChild(document.createTextNode(QString::number(matrixGamma2[i][4])));
        gammaParameters2.appendChild(wmaxGammaFunction2);

        QDomElement wminGammaFunction2 =document.createElement( "wmin" );
        wminGammaFunction2.appendChild(document.createTextNode(QString::number(matrixGamma2[i][5])));
        gammaParameters2.appendChild(wminGammaFunction2);

        QDomElement paGammaFunction2 =document.createElement( "pa" );
        paGammaFunction2.appendChild(document.createTextNode(QString::number(matrixGamma2[i][6])));
        gammaParameters2.appendChild(paGammaFunction2);

        QDomElement pbGammaFunction2 =document.createElement( "pb" );
        pbGammaFunction2.appendChild(document.createTextNode(QString::number(matrixGamma2[i][7])));
        gammaParameters2.appendChild(pbGammaFunction2);

        QDomElement pwGammaFunction2 =document.createElement( "pw" );
        pwGammaFunction2.appendChild(document.createTextNode(QString::number(matrixGamma2[i][8])));
        gammaParameters2.appendChild(pwGammaFunction2);

        QDomElement maxtransGammaFunction1 =document.createElement( "tmax" );
        maxtransGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma2[i][9])));
        gammaParameters2.appendChild(maxtransGammaFunction1);

        QDomElement mintransGammaFunction1 =document.createElement( "tmin" );
        mintransGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma2[i][10])));
        gammaParameters2.appendChild(mintransGammaFunction1);

        QDomElement perctransGammaFunction1 =document.createElement( "pt" );
        perctransGammaFunction1.appendChild(document.createTextNode(QString::number(matrixGamma2[i][11])));
        gammaParameters2.appendChild(perctransGammaFunction1);

        gammaFunction2.appendChild(gammaParameters2);
    }

    return gammaFunction2;
}

QDomElement XMLManager::getLinearElementXML(std::vector<std::vector<double> > matrixLinear, QDomDocument document)
{
    QDomElement linearFunction =document.createElement( "LinearFunction" );
    QDomElement numberLinearFunction =document.createElement( "Number" );
    numberLinearFunction.appendChild(document.createTextNode(QString::number(matrixLinear.size())));
    linearFunction.appendChild(numberLinearFunction);

    for (size_t i = 0; i < matrixLinear.size(); i++) {
        QDomElement linearParameters =document.createElement( "Parameters" );
        QDomElement factorMaxLinearFunction =document.createElement( "factormax" );
        factorMaxLinearFunction.appendChild(document.createTextNode(QString::number(matrixLinear[i][0])));
        linearParameters.appendChild(factorMaxLinearFunction);

        QDomElement factorMinLinearFunction =document.createElement( "factormin" );
        factorMinLinearFunction.appendChild(document.createTextNode(QString::number(matrixLinear[i][1])));
        linearParameters.appendChild(factorMinLinearFunction);

        QDomElement interceptMaxLinearFunction =document.createElement( "interceptmax" );
        interceptMaxLinearFunction.appendChild(document.createTextNode(QString::number(matrixLinear[i][2])));
        linearParameters.appendChild(interceptMaxLinearFunction);

        QDomElement interceptMinLinearFunction =document.createElement( "interceptmin" );
        interceptMinLinearFunction.appendChild(document.createTextNode(QString::number(matrixLinear[i][3])));
        linearParameters.appendChild(interceptMinLinearFunction);

        QDomElement wmaxGammaFunction2 =document.createElement( "wmax" );
        wmaxGammaFunction2.appendChild(document.createTextNode(QString::number(matrixLinear[i][4])));
        linearParameters.appendChild(wmaxGammaFunction2);

        QDomElement wminGammaFunction2 =document.createElement( "wmin" );
        wminGammaFunction2.appendChild(document.createTextNode(QString::number(matrixLinear[i][5])));
        linearParameters.appendChild(wminGammaFunction2);

        QDomElement paGammaFunction2 =document.createElement( "pa" );
        paGammaFunction2.appendChild(document.createTextNode(QString::number(matrixLinear[i][6])));
        linearParameters.appendChild(paGammaFunction2);

        QDomElement pbGammaFunction2 =document.createElement( "pb" );
        pbGammaFunction2.appendChild(document.createTextNode(QString::number(matrixLinear[i][7])));
        linearParameters.appendChild(pbGammaFunction2);

        QDomElement pwGammaFunction2 =document.createElement( "pw" );
        pwGammaFunction2.appendChild(document.createTextNode(QString::number(matrixLinear[i][8])));
        linearParameters.appendChild(pwGammaFunction2);

        QDomElement maxtransGammaFunction1 =document.createElement( "tmax" );
        maxtransGammaFunction1.appendChild(document.createTextNode(QString::number(matrixLinear[i][9])));
        linearParameters.appendChild(maxtransGammaFunction1);

        QDomElement mintransGammaFunction1 =document.createElement( "tmin" );
        mintransGammaFunction1.appendChild(document.createTextNode(QString::number(matrixLinear[i][10])));
        linearParameters.appendChild(mintransGammaFunction1);

        QDomElement perctransGammaFunction1 =document.createElement( "pt" );
        perctransGammaFunction1.appendChild(document.createTextNode(QString::number(matrixLinear[i][11])));
        linearParameters.appendChild(perctransGammaFunction1);


        linearFunction.appendChild(linearParameters);
    }

    return linearFunction;
}

int XMLManager::SaveXMLFileRegressionProject(const QString &_projectName,
                                              const QString &selection,
                                              const QString &value1,
                                              const QString &value2,
                                              const QString &populationSize,
                                              const QString &percentageCrossover,
                                              const QString &percentageMutation,
                                              const  QString &numberProcessor,
                                              const  QString &maxGeneration,
                                              const  QString &_fileKernel,
                                              std::vector<std::vector<double> > matrixGamma1,
                                              std::vector<std::vector<double> > matrixGamma2,
                                              std::vector<std::vector<double> > matrixLinear,
                                              const QString &checkControlPointsWithN,
                                              const QString &textN,
                                              const QString typeExecution
                                              , QString typeReplacement, QString numberElitist){
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

//    qDebug() << "NumProjects = "<<document.childNodes().at(1).childNodes().at(0).firstChild().nodeValue();
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
    QDomElement numberProcessorElement = document.createElement( "numberProcessor" );
    QDomElement probabilityOfCrossoverElement = document.createElement( "ProbabilityOfCrossover" );
    QDomElement probabilityOfMutationElement = document.createElement( "ProbabilityOfMutation" );
    QDomElement maximumNumberOfGenerationsElement = document.createElement( "MaximumNumberOfGenerations" );
    QDomElement fileKernel = document.createElement( "FileKernel" );
    QDomElement checkControlPointsWithNElement = document.createElement( "CheckN" );
    checkControlPointsWithNElement.appendChild(document.createTextNode(checkControlPointsWithN));
    QDomElement textNElement = document.createElement( "N" );
    textNElement.appendChild(document.createTextNode(textN));
    QDomElement typeExcecution = document.createElement( "typeExcecution" );
    typeExcecution.appendChild(document.createTextNode(typeExecution));
    QDomElement typeReplacementDom = document.createElement( "typeReplacement" );
    QDomElement numberElitistDom = document.createElement( "numberElitist" );

    //create TextElement
    QDomText nameText = document.createTextNode(_projectName);
    QDomText typeText = document.createTextNode( selection );
    QDomText value1Text = document.createTextNode( value1 );
    QDomText value2Text = document.createTextNode( value2 );
    QDomText populationSizeElementText = document.createTextNode( populationSize );
    QDomText probabilityOfCrossoverElementText = document.createTextNode( percentageCrossover );
    QDomText probabilityOfMutationElementText = document.createTextNode( percentageMutation );
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

    numberProcessorElement.appendChild(document.createTextNode(QString("%1").arg(numberProcessor)));
    project.appendChild(numberProcessorElement);

    probabilityOfCrossoverElement.appendChild(probabilityOfCrossoverElementText);
    project.appendChild(probabilityOfCrossoverElement);

    probabilityOfMutationElement.appendChild(probabilityOfMutationElementText);
    project.appendChild(probabilityOfMutationElement);

    maximumNumberOfGenerationsElement.appendChild(maximumNumberOfGenerationsElementText);
    project.appendChild(maximumNumberOfGenerationsElement);

    fileKernel.appendChild(fileKernelText);
    project.appendChild(fileKernel);
    project.appendChild(checkControlPointsWithNElement);
    project.appendChild(textNElement);
    project.appendChild(typeExcecution);
    QDomText typeReplacementText = document.createTextNode( typeReplacement );
    QDomText numberElitistText = document.createTextNode( numberElitist );
    typeReplacementDom.appendChild(typeReplacementText);
    numberElitistDom.appendChild(numberElitistText);
    project.appendChild(typeReplacementDom);
    project.appendChild(numberElitistDom);

    QDomElement gammaFunction1 = getGamma1ElementXML(matrixGamma1, document);

    project.appendChild(gammaFunction1);

    QDomElement gammaFunction2 = getGamma2ElementXML(matrixGamma2, document);
    project.appendChild(gammaFunction2);

    QDomElement linearFunction = getLinearElementXML(matrixLinear, document);
    project.appendChild(linearFunction);




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
                                                         const  QString &numberProcessor,
                                                         const  QString &maxGeneration,
                                                         const  QString &_fileKernel,
                                                         std::vector<std::vector<double> > matrixGamma1,
                                                         std::vector<std::vector<double> > matrixGamma2,
                                                         std::vector<std::vector<double> > matrixLinear,
                                                         const QString &checkControlPointsWithN,
                                                         const QString &textN,
                                                         const QString &typeExecution,
                                                         QString typeReplacement,
                                                         QString numberElitist){
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
    QDomNodeList project = documentElement.elementsByTagName("RegressionProject");
    for (int i = 0; i < project.length(); i++) {
        //TODO Find the project with the save name (next future find with id)
        int result = QString::compare(project.at(i).childNodes().at(0).firstChild().nodeValue(), name, Qt::CaseInsensitive);
        if(result==0){
            //std::cout << "trovato" << std::endl;
            project.at(i).childNodes().at(1).childNodes().at(0).firstChild().setNodeValue(selection);
            project.at(i).childNodes().at(1).childNodes().at(1).firstChild().setNodeValue(value1);
            project.at(i).childNodes().at(1).childNodes().at(2).firstChild().setNodeValue(value2);
            project.at(i).childNodes().at(2).firstChild().setNodeValue(populationSize);
            project.at(i).childNodes().at(3).firstChild().setNodeValue(numberProcessor);
            project.at(i).childNodes().at(4).firstChild().setNodeValue(percentageCrossover);
            project.at(i).childNodes().at(5).firstChild().setNodeValue(percentageMutation);
            project.at(i).childNodes().at(6).firstChild().setNodeValue(maxGeneration);
            project.at(i).childNodes().at(7).firstChild().setNodeValue(_fileKernel);
            project.at(i).childNodes().at(8).firstChild().setNodeValue(checkControlPointsWithN);
            project.at(i).childNodes().at(9).firstChild().setNodeValue(textN);
            project.at(i).childNodes().at(10).firstChild().setNodeValue(typeExecution);
            project.at(i).childNodes().at(11).firstChild().setNodeValue(typeReplacement);
            project.at(i).childNodes().at(12).firstChild().setNodeValue(numberElitist);

            int tmpID = project.at(i).childNodes().at(16).firstChild().nodeValue().toInt();
            project.at(i).removeChild(project.at(i).childNodes().at(16));
            project.at(i).removeChild(project.at(i).childNodes().at(15));
            project.at(i).removeChild(project.at(i).childNodes().at(14));
            project.at(i).removeChild(project.at(i).childNodes().at(13));

            QDomElement gammaFunction1 = getGamma1ElementXML(matrixGamma1, document);
            project.at(i).appendChild(gammaFunction1);
            QDomElement gammaFunction2 = getGamma2ElementXML(matrixGamma2, document);
            project.at(i).appendChild(gammaFunction2);
            QDomElement linearFunction = getLinearElementXML(matrixLinear, document);
            project.at(i).appendChild(linearFunction);
            QDomElement id = document.createElement( "ID" );
            id.appendChild(document.createTextNode(QString("%1").arg(tmpID)));
            project.at(i).appendChild(id);


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

bool XMLManager::deleteProject(int idProject)
{


    QFile inFile( xmlFilePath );

    if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for reading." );
        return false;
    }

    QDomDocument document;
    if( !document.setContent( &inFile ) )
    {
        qDebug( "Failed to parse the file into a DOM tree." );
        inFile.close();
        return false;
    }

     inFile.close();

    QDomElement documentElement = document.documentElement();
    QDomNodeList a = documentElement.elementsByTagName("ID");
    for (int i = 0; i < a.length(); i++) {
        if(QString::compare(a.at(i).firstChild().nodeValue(), QString::number(idProject), Qt::CaseInsensitive)==0){
            QDomNode parent = a.at(i).parentNode();
            QDomNode first = parent.parentNode();
            QDomNode returnNode = first.removeChild(parent);
            if(returnNode.isNull())
                return false;
        }
    }

    if (!inFile.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        qDebug("Basically, now we lost content of a file");
        return false;
    }
    QByteArray xml = document.toByteArray();
    inFile.write(xml);
    inFile.close();


    return true;
}

