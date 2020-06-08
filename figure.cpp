#include "figure.h"

Figure::Figure(bool IsWhite, bool IsQueen, QPoint Position):isWhite{IsWhite},isQueen{IsQueen},position{Position}{}

void Figure::setIsWhite(bool IsWhite){isWhite=IsWhite;}
bool Figure::getIsWhite()const{return isWhite;}

void Figure::setIsQueen(bool IsQueen){isQueen=IsQueen;}
bool Figure::getIsQueen()const{return isQueen;}

void Figure::setIsFirstPlayr(bool IsFirstPlayr){isFirstPlayer=IsFirstPlayr;}
bool Figure::getIsFirstPlayr()const{return isFirstPlayer;}

void Figure::setPosition(QPoint Position){position= Position;}
QPoint Figure::getPosition()const{return position;}

void Figure::setIsBlokedState(bool IsBlokedState){isBlokedState= IsBlokedState;}
bool Figure::getIsBlokedState()const{return isBlokedState;}

void Figure::setVPathway(QVector<Pathway> VPathway){vPathway<< VPathway;}
void Figure::setVPathway(Pathway pathway){vPathway<< pathway;}
QVector<Pathway> Figure::getVPathway()const {return  vPathway;}


Figure::~Figure(){}


void Figure::clearPathway(){ if (!vPathway.empty()) { vPathway.clear(); }}


QVector<Pathway> Figure::figureDirectionBeats (QPoint Position, const Direction direction, const bool IsWhite, ViewLabel* doubArrayViewLabel[8][8])const{
    #define notEmptyNextCell(x,y) doubArrayViewLabel[x][y] != nullptr
    #define    emptyNextCell(x,y) doubArrayViewLabel[x][y] == nullptr
    #define            alien(x,y) doubArrayViewLabel[x][y]->getIsWhite() != IsWhite

    #define Upper_LeftPoint  QPoint(x-1,y-1)
    #define Upper_RightPoint QPoint(x+1,y-1)
    #define  Down_LeftPoint  QPoint(x-1,y+1)
    #define  Down_RightPoint QPoint(x+1,y+1)

    #define Upper_LeftJump  QPoint(x-2,y-2)
    #define Upper_RightJump QPoint(x+2,y-2)
    #define  Down_LeftJump  QPoint(x-2,y+2)
    #define  Down_RightJump QPoint(x+2,y+2)

    #define  UpperLeft  (x>1)&&(y>1)
    #define  UpperRight (x<6)&&(y>1)
    #define  DownLeft   (x>1)&&(y<6)
    #define  DownRight  (x<6)&&(y<6)

    QVector<Pathway> vPathway;
    vPathway.clear();              //?????????????????

    int x = Position.x();
    int y = Position.y();

    bool nextCell=false;
    bool nextCellJump=false;

    switch (direction) {

    case Upper_Left:
       if (UpperLeft) {
           nextCell =  notEmptyNextCell(x-1,y-1);
           nextCellJump = emptyNextCell(x-2,y-2);
           if (nextCell && nextCellJump) {
               if (alien(x-1,y-1)) {
               Pathway curentPathway = Pathway(Upper_LeftJump);
               curentPathway.setCount(1);
               curentPathway.setDownedPoints(Upper_LeftPoint);
               curentPathway.setDirection(direction);
               vPathway<<curentPathway;
               }
           }
       }
       break;

    case Upper_Right:
       if (UpperRight) {
           nextCell =  notEmptyNextCell(x+1,y-1);
           nextCellJump = emptyNextCell(x+2,y-2);
           if (nextCell && nextCellJump) {
               if (alien(x+1,y-1)) {
               Pathway curentPathway = Pathway(Upper_LeftJump);
               curentPathway.setCount(1);
               curentPathway.setDownedPoints(Upper_LeftPoint);
               curentPathway.setDirection(direction);
               vPathway<<curentPathway;
               }
           }
       }
       break;

    case Down_Left:
       if (DownLeft) {
           nextCell =  notEmptyNextCell(x-1,y+1);
           nextCellJump = emptyNextCell(x-2,y+2);
           if (nextCell && nextCellJump) {
               if (alien(x-1,y+1)) {
               Pathway curentPathway = Pathway(Upper_LeftJump);
               curentPathway.setCount(1);
               curentPathway.setDownedPoints(Upper_LeftPoint);
               curentPathway.setDirection(direction);
               vPathway<<curentPathway;
               }
           }
       }
       break;

    case Down_Right:
       if (DownRight) {
           nextCell =  notEmptyNextCell(x+1,y+1);
           nextCellJump = emptyNextCell(x+2,y+2);
           if (nextCell && nextCellJump) {
               if (alien(x+1,y+1)) {
               Pathway curentPathway = Pathway(Upper_LeftJump);
               curentPathway.setCount(1);
               curentPathway.setDownedPoints(Upper_LeftPoint);
               curentPathway.setDirection(direction);
               vPathway<<curentPathway;
               }
           }
       }
       break;

   } // switch


   return vPathway;
}


QVector<Pathway> Figure::pawnStep(ViewLabel* const doubArrayViewLabel[8][8])const{
    #define isEmptyNextCell(x,y) doubArrayViewLabel[x][y] == nullptr
    #define Upper_LeftPoint  QPoint(x-1,y-1)
    #define Upper_RightPoint QPoint(x+1,y-1)
    #define  Down_LeftPoint  QPoint(x-1,y+1)
    #define  Down_RightPoint QPoint(x+1,y+1)

    bool nextCell=false;
    QVector<Pathway> vPathway;
    int x = getPosition().x();
    int y = getPosition().y();
    if (getIsFirstPlayr()) {
        ///////////////////////////////  UPPER   ////////////////////////
        if ((x>0) && (y>0)) {
            nextCell = isEmptyNextCell(x-1,y-1);
            if (nextCell) {vPathway<<Pathway(Upper_LeftPoint); }
        }
        if ((x<7) && (y>0)) {
            nextCell = isEmptyNextCell(x+1,y-1);
            if (nextCell) {vPathway<<Pathway(Upper_RightPoint); }
        }
    }
    else {
        ///////////////////////////////  DOWN  //////////////////////////
        if ((x>0) && (y<7)) {
            nextCell = isEmptyNextCell(x-1,y+1);
            if (nextCell) {vPathway<<Pathway(Down_LeftPoint); }
        }
        if ((x<7) && (y<7)) {
            nextCell = isEmptyNextCell(x+1,y+1);
            if (nextCell) {vPathway<<Pathway(Down_RightPoint); }
        }
    }
    return vPathway;
}


QVector<Pathway> Figure::pawnBeats(QPoint Position, bool IsWhite, bool IsFirstPlayer, ViewLabel* doubArrayViewLabel[8][8])const{
#define notEmptyNextCell(x,y) doubArrayViewLabel[x][y] != nullptr
#define    emptyNextCell(x,y) doubArrayViewLabel[x][y] == nullptr
#define            alien(x,y) doubArrayViewLabel[x][y]->getIsWhite() != IsWhite

//#define  UpperLeft  (x>1)&&(y>1)

#define Upper_LeftPoint  QPoint(x-1,y-1)
#define Upper_RightPoint QPoint(x+1,y-1)
#define  Down_LeftPoint  QPoint(x-1,y+1)
#define  Down_RightPoint QPoint(x+1,y+1)

#define Upper_LeftJump  QPoint(x-2,y-2)
#define Upper_RightJump QPoint(x+2,y-2)
#define  Down_LeftJump  QPoint(x-2,y+2)
#define  Down_RightJump QPoint(x+2,y+2)

    //
//    ViewLabel* doubArrayViewLabelCopy[8][8];
//        for (int x=0;x<8;x++) {
//            for (int y=0;y<8;y++) {
//                doubArrayViewLabelCopy[x][y]= doubArrayViewLabel[x][y];
//            }
//        }


    //

    QVector<Pathway> vPathway;
    vPathway.clear();
    int x = Position.x();
    int y = Position.y();
    //не дальше зоны противника
    if (IsFirstPlayer && y==0) {
        return vPathway;
    }
    if (!IsFirstPlayer && y==7) {
        return vPathway;
    }

    bool nextCell=false;
    bool nextCellJump=false;
    ViewLabel* I_AM =doubArrayViewLabel[x][y];
    doubArrayViewLabel[x][y]=nullptr;              //<---------------&7777777777
    QVector<Direction> vDirection;
    vDirection<<Upper_Left<<Upper_Right<<Down_Left<<Down_Right;



    for (Direction direction : vDirection) {

        switch (direction) {
        case Upper_Left:
            if ((x>1) && (y>1)) {
                nextCell =  notEmptyNextCell(x-1,y-1);
                nextCellJump = emptyNextCell(x-2,y-2);
                if (nextCell && nextCellJump) {
                    if (alien(x-1,y-1)) {
                    Pathway curentPathway = Pathway(Upper_LeftJump);
                    curentPathway.setCount(1);
                    curentPathway.setDownedPoints(Upper_LeftPoint);
                    ViewLabel* copyViewLabel=doubArrayViewLabel[x-1][y-1];
                    doubArrayViewLabel[x-1][y-1]=nullptr;
                    QVector<Pathway> vAfterPathway;
                    vAfterPathway << pawnBeats(Upper_LeftJump, IsWhite, IsFirstPlayer, doubArrayViewLabel);
                    if (!vAfterPathway.empty()) {
                        for (Pathway pathway : vAfterPathway) {
                            vPathway<<pathway+curentPathway;
                            }
                        doubArrayViewLabel[x-1][y-1]=copyViewLabel;
                        break;

                    }
                    vPathway<<curentPathway;
                    doubArrayViewLabel[x-1][y-1]=copyViewLabel;
                    }
                }
            }
            break;

        case Upper_Right:
            if ((x<6) && (y>1)) {
                nextCell =  notEmptyNextCell(x+1,y-1);
                nextCellJump = emptyNextCell(x+2,y-2);
                if (nextCell && nextCellJump) {
                    if (alien(x+1,y-1)) {
                    Pathway curentPathway = Pathway(Upper_RightJump);
                    curentPathway.setCount(1);
                    curentPathway.setDownedPoints(Upper_RightPoint);
                    ViewLabel* copyViewLabel=doubArrayViewLabel[x+1][y-1];
                    doubArrayViewLabel[x+1][y-1]=nullptr;
                    QVector<Pathway> vAfterPathway;
                    vAfterPathway << pawnBeats(Upper_RightJump, IsWhite, IsFirstPlayer, doubArrayViewLabel);
                    if (!vAfterPathway.empty() ) {
                        for (Pathway pathway : vAfterPathway) {
                            vPathway<<pathway+curentPathway;
                            }
                        doubArrayViewLabel[x+1][y-1]=copyViewLabel;
                        break;

                    }
                    vPathway<<curentPathway;
                    doubArrayViewLabel[x+1][y-1]=copyViewLabel;
                    }
                }
            }
            break;

        case Down_Left:
            if ((x>1) && (y<6)) {
                nextCell =  notEmptyNextCell(x-1,y+1);
                nextCellJump = emptyNextCell(x-2,y+2);
                if (nextCell && nextCellJump) {
                    if (alien(x-1,y+1)) {
                    Pathway curentPathway = Pathway(Down_LeftJump);
                    curentPathway.setCount(1);
                    curentPathway.setDownedPoints(Down_LeftPoint);
                    ViewLabel* copyViewLabel=doubArrayViewLabel[x-1][y+1];
                    doubArrayViewLabel[x-1][y+1]=nullptr;
                    QVector<Pathway> vAfterPathway;
                    vAfterPathway << pawnBeats(Down_LeftJump, IsWhite, !IsFirstPlayer, doubArrayViewLabel);
                    if (!vAfterPathway.empty()) {
                        for (Pathway pathway : vAfterPathway) {
                            vPathway<<pathway+curentPathway;
                            }
                        doubArrayViewLabel[x-1][y+1]=copyViewLabel;
                        break;

                    }
                    vPathway<<curentPathway;
                    doubArrayViewLabel[x-1][y+1]=copyViewLabel;
                    }
                }
            }
            break;

        case Down_Right:
            if ((x<6) && (y<6)) {
                nextCell =  notEmptyNextCell(x+1,y+1);
                nextCellJump = emptyNextCell(x+2,y+2);
                if (nextCell && nextCellJump) {
                    if (alien(x+1,y+1)) {
                    Pathway curentPathway = Pathway(Down_RightJump);
                    curentPathway.setCount(1);
                    curentPathway.setDownedPoints(Down_RightPoint);
                    ViewLabel* copyViewLabel=doubArrayViewLabel[x+1][y+1];
                    doubArrayViewLabel[x+1][y+1]=nullptr;
                    QVector<Pathway> vAfterPathway;
                    vAfterPathway << pawnBeats(Down_RightJump, IsWhite, !IsFirstPlayer, doubArrayViewLabel);
                    if (!vAfterPathway.empty()) {
                        for (Pathway pathway : vAfterPathway) {
                            vPathway<<pathway+curentPathway;
                            }
                        doubArrayViewLabel[x+1][y+1]=copyViewLabel;
                        break;

                    }
                    vPathway<<curentPathway;
                    doubArrayViewLabel[x+1][y+1]=copyViewLabel;
                    }
                }
            }
            break;



        }
    }//for

    doubArrayViewLabel[x][y]=I_AM;
    return vPathway;
}


QVector<Pathway> Figure::emptyWay(QPoint Position, const Direction direction, ViewLabel* doubArrayViewLabel[8][8])const{
#define isEmptyNextCell(x,y) doubArrayViewLabel[x][y] == nullptr
#define Upper_LeftPoint  QPoint(x-1,y-1)
#define Upper_RightPoint QPoint(x+1,y-1)
#define  Down_LeftPoint  QPoint(x-1,y+1)
#define  Down_RightPoint QPoint(x+1,y+1)

    bool nextCell=false;
    QVector<Pathway> vPathway;
    int x = Position.x();
    int y = Position.y();

    switch (direction) {

    case Upper_Left:
        if ((x>0) && (y>0)) {
            nextCell = isEmptyNextCell(x-1,y-1);
            if (nextCell) {
                Pathway pathway(Upper_LeftPoint);
                pathway.setDirection(Upper_Left);
                vPathway<<pathway;
                vPathway<<emptyWay(Upper_LeftPoint, direction, doubArrayViewLabel);
            }
        }
        break;

    case Upper_Right:
        if ((x<7) && (y>0)) {
            nextCell = isEmptyNextCell(x+1,y-1);
            if (nextCell) {
                Pathway pathway(Upper_RightPoint);
                pathway.setDirection(Upper_Right);
                vPathway<<pathway;
                vPathway<<emptyWay(Upper_RightPoint, direction, doubArrayViewLabel);
            }
        }
        break;

    case Down_Left:
        if ((x>0) && (y<7)) {
            nextCell = isEmptyNextCell(x-1,y+1);
            if (nextCell) {
                Pathway pathway(Down_LeftPoint);
                pathway.setDirection(Down_Left);
                vPathway<<pathway;
                vPathway<<emptyWay(Down_LeftPoint, direction, doubArrayViewLabel);
            }
        }
        break;

    case Down_Right:
        if ((x<7) && (y<7)) {
            nextCell = isEmptyNextCell(x+1,y+1);
            if (nextCell) {
                Pathway pathway(Down_RightPoint);
                pathway.setDirection(Down_Right);
                vPathway<<pathway;
                vPathway<<emptyWay(Down_RightPoint, direction, doubArrayViewLabel);
            }
        }
        break;

    }

    return vPathway;
}


QVector<Pathway> Figure::queenBeats(QPoint Position, const bool IsWhite, ViewLabel* doubArrayViewLabel[8][8])const{
#define notEmptyNextCell(x,y) doubArrayViewLabel[x][y] != nullptr
#define    emptyNextCell(x,y) doubArrayViewLabel[x][y] == nullptr
#define            alien(x,y) doubArrayViewLabel[x][y]->getIsWhite() != IsWhite


#define Upper_LeftPoint  QPoint(x-1,y-1)
#define Upper_RightPoint QPoint(x+1,y-1)
#define  Down_LeftPoint  QPoint(x-1,y+1)
#define  Down_RightPoint QPoint(x+1,y+1)

#define Upper_LeftJump  QPoint(x-2,y-2)
#define Upper_RightJump QPoint(x+2,y-2)
#define  Down_LeftJump  QPoint(x-2,y+2)
#define  Down_RightJump QPoint(x+2,y+2)

#define  UpperLeft  (x>1)&&(y>1)
#define  UpperRight (x<6)&&(y>1)
#define  DownLeft   (x>1)&&(y<6)
#define  DownRight  (x<6)&&(y<6)

    QVector<Pathway> vPathway;
    vPathway.clear();
    int x = Position.x();
    int y = Position.y();


    bool nextCell=false;
    bool nextCellJump=false;
    //ViewLabel* I_AM =doubArrayViewLabel[x][y];
    //doubArrayViewLabel[x][y]=nullptr;              //<---------------&7777777777
    QVector<Direction> vDirection;
    vDirection<<Upper_Left<<Upper_Right<<Down_Left<<Down_Right;



    for (Direction direction : vDirection) {

        switch (direction) {
        case Upper_Left:
            if (UpperLeft) {

            }
            break;

        case Upper_Right:
            if (UpperRight) {

            }
            break;

        case Down_Left:
            if (DownLeft) {

            }
            break;

        case Down_Right:
            if (DownRight) {

            }
            break;



        }
    }//for

    //doubArrayViewLabel[x][y]=I_AM;
    return vPathway;
}


QVector<Pathway> Figure::queenDirectionBeats (const QPoint Position, const Direction direction, const bool IsWhite, ViewLabel* doubArrayViewLabel[8][8]){
#define notEmptyNextCell(x,y) doubArrayViewLabel[x][y] != nullptr
#define    emptyNextCell(x,y) doubArrayViewLabel[x][y] == nullptr
#define            alien(x,y) doubArrayViewLabel[x][y]->getIsWhite() != IsWhite


#define Upper_LeftPoint  QPoint(x-1,y-1)
#define Upper_RightPoint QPoint(x+1,y-1)
#define  Down_LeftPoint  QPoint(x-1,y+1)
#define  Down_RightPoint QPoint(x+1,y+1)

#define Upper_LeftJump  QPoint(x-2,y-2)
#define Upper_RightJump QPoint(x+2,y-2)
#define  Down_LeftJump  QPoint(x-2,y+2)
#define  Down_RightJump QPoint(x+2,y+2)

#define  UpperLeft  (x>1)&&(y>1)
#define  UpperRight (x<6)&&(y>1)
#define  DownLeft   (x>1)&&(y<6)
#define  DownRight  (x<6)&&(y<6)



    int x = Position.x();
    int y = Position.y();

    bool firstPass{true};
    bool nextCell=false;
    bool nextCellJump=false;

    QVector<Pathway> vPathway;
    //vPathway.clear();
    QVector<Pathway> vEmptyWay;
    QVector<Pathway> vCurentPathway;








    switch (direction) {

    case Upper_Left:
        if (UpperLeft) {
            //first step
            vEmptyWay<<emptyWay(Position,direction,doubArrayViewLabel);
            if (!vEmptyWay.empty()) {
                Pathway endPathway = vEmptyWay.back();
                QPoint endPoint = endPathway.getPosition();
                vCurentPathway<<figureDirectionBeats(endPoint,direction,IsWhite,doubArrayViewLabel);
            }
            else {vCurentPathway<<figureDirectionBeats(Position,direction,IsWhite,doubArrayViewLabel);}
            //next step
            if (!vCurentPathway.empty()) {
todo  there is one Pathway
            }



        }
        break;

    case Upper_Right:
        if (UpperRight) {

        }
        break;

    case Down_Left:
        if (DownLeft) {

        }
        break;

    case Down_Right:
        if (DownRight) {

        }
        break;



    }


    //doubArrayViewLabel[x][y]=I_AM;
    return vPathway;
}




