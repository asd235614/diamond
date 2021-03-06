//
//  Play.cpp
//  
// 1、判断消除的是那种颜色，让宠物前进
// 2、判断宠物是否能攻击怪兽了
// 3、宝石被消除后也会攻击怪兽，3消4消5消等攻击的血量不同
// 4、记得宝石下落后再判定有没有可消除的
// 5、最最最最重要的：读取棋盘信息是从本地的一个文件读取的，什么文件，文件什么格式看你喜欢
//
//

#include "PlayScene.h"
Scene * Play::createScene(int level,int pets){
    auto scene=Scene::create();
    auto layer=Play::create();
    scene->addChild(layer);
    return scene;
}
bool Play::init(){
    if(!Layer::init())
    {
        return false;
    }
    //添加游戏标题
    auto lab=Label::createWithSystemFont("刀塔消消乐","", 35);
    this->addChild(lab);
    lab->setPosition(150,Director::getInstance()->getWinSize().height-50);
    //添加游戏地图
    for (int r=0; r<7; r++) {
        for(int c=0;c<7;c++)
        {
            map[r][c]=DiamondSprite::createDiamondSprite(random()%7+1, r, c);
            this->addChild(map[r][c]);
            
        }
    }
//    添加侦听
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchBegan=CC_CALLBACK_2(Play::onTouchBegan,this);
    listener->onTouchMoved=CC_CALLBACK_2(Play::onTouchMoved,this);
    listener->onTouchEnded=CC_CALLBACK_2(Play::onTouchEnded,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}
bool Play::onTouchBegan(Touch *touch, Event *unused_event){
    startX=touch->getLocation().x;
    startY=touch->getLocation().y;
    return true;
}
void Play::onTouchMoved(Touch *touch, Event *unused_event){}
void Play::onTouchEnded(Touch *touch, Event *unused_event){
    int w=abs(touch->getLocation().x-startX);
    int h=abs(touch->getLocation().y-startY);
    if ((w<5&&h<5)||startX>640||startY>640) {
        return;
    }
    int nowrow=startY/80;
    int nowcol=startX/80;
    if (w>h) {
        if(touch->getLocation().x>startX)
        {
            Play::moveDiamondSprite(GAMEDIR::DIR_RIGHT,nowrow,nowcol);
        }else{
         Play::moveDiamondSprite(GAMEDIR::DIR_LEFT,nowrow,nowcol);
        }
    }else{
        if(touch->getLocation().y>startY)
        {
            Play::moveDiamondSprite(GAMEDIR::DIR_UP,nowrow,nowcol);
        }else{
            Play::moveDiamondSprite(GAMEDIR::DIR_DOWN,nowrow,nowcol);
        }
    }

}
void Play::moveDiamondSprite(GAMEDIR d,int r,int c){

    //    确定方向
    switch (d) {
        case GAMEDIR::DIR_LEFT:
        if(c-1>=0)
            
        {
            map[r][c]->moveTo(r, c-1);
            map[r][c-1]->moveTo(r, c);
           
            DiamondSprite * tmp=map[r][c];
            map[r][c]=map[r][c-1];
            map[r][c-1]=tmp;
           

        }
            break;
        case GAMEDIR::DIR_RIGHT:
            if(c+1<7)
            {  map[r][c]->moveTo(r, c+1);
                map[r][c+1]->moveTo(r, c);
                DiamondSprite * tmp=map[r][c];
                map[r][c]=map[r][c+1];
                map[r][c+1]=tmp;
              
            }
            break;
        case GAMEDIR::DIR_UP:
            if(r+1<7)
            {   map[r][c]->moveTo(r+1, c);
                map[r+1][c]->moveTo(r, c);
                DiamondSprite * tmp=map[r][c];
                map[r][c]=map[r+1][c];
                map[r+1][c]=tmp;
              
            }
            break;
        case GAMEDIR::DIR_DOWN:
            if(r-1>=0)
            {
                map[r][c]->moveTo(r-1, c);
                map[r-1][c]->moveTo(r, c);
                DiamondSprite * tmp=map[r][c];
                map[r][c]=map[r-1][c];
                map[r-1][c]=tmp;
                
            }
            break;
        default:
            break;
    }
    if(!removeDiamondSprite())
    {//交换回来
    
    }
}
bool Play::removeDiamondSprite()//消除卡片
{
    //如果有3个以上连续3行或3列相同的怪物则消除
    for(int r=0;r<7;r++) //判断7行里面每行是否有可以消除的
    {   for(int c=0;c<=4;c++)
       {  int num=map[r][c]->number; //获取map[r][c]的怪物编号
           int samnum=0;
           int nowcol=0;
           for(nowcol=c+1; nowcol<7; nowcol++) {
            if(num==map[r][nowcol]->number)
            {
                samnum++;
            }else
            {break;
            }
          }
          //判断samenum
           if(samnum>=2) //消除所有相同的
           {
               for(int tmp=c;tmp<nowcol;tmp++)
               {
                   map[r][tmp]->canRemove=true;
               }
           }
        }
    }
    for (int c=0; c<7; c++) {
        //判断map[r][c]周围是否有连续3个可以
        for(int r=0;r<=4;r++)
        {  int num=map[r][c]->number; //获取map[r][c]的怪物编号
            int samnum=0;
            int nowrow=0;
            for(nowrow=r+1; nowrow<7; nowrow++) {
                if(num==map[nowrow][c]->number)
                {
                    samnum++;
                }else
                {break;
                }
            }
            //判断samenum
            if(samnum>=2) //消除所有相同的
            {
                for(int tmp=r;tmp<nowrow;tmp++)
                {
                    map[tmp][c]->canRemove=true;
                }
            }
        }

        
    }
    //统一删除所有标记为canRemove=true的
    for(int r=0;r<7;r++) //判断7行里面每行是否有可以消除的
    {   for(int c=0;c<7;c++)
      {
        if(map[r][c]->canRemove)
        {
            this->removeChild(map[r][c]);
            map[r][c]=nullptr;
        }
       }
    }
    autoDownDiamondSprite();
    return true;
}
 void Play::autoDownDiamondSprite()//自动掉落
{
    down();
    //判断为空的地方自动下落补齐
    for (int r=0; r<7; r++) {
        for (int c=0; c<7; c++) {
            if(map[r][c]==nullptr)
            {
                map[r][c]=DiamondSprite::createDiamondSprite(random()%7+1, r, c);
                this->addChild(map[r][c]);
            }
        }
    }
    

}
 void Play::down()//落下
{
    for(int r=0;r<7;r++)
    { for(int c=0;c<7;c++)
      { if(map[r][c]==nullptr)
       { //让他上方的所有块向下移动
        for(int tmprow=r;tmprow<6;tmprow++)
        {
            if(map[tmprow+1][c]!=nullptr)
                {CCLOG("r%d c %d down",tmprow+1,c);
                map[tmprow+1][c]->moveTo(tmprow, c);
                map[tmprow][c]=map[tmprow+1][c];
                map[tmprow+1][c]=nullptr;
            }
        }
      }
     }
    }
    for(int r=0;r<6;r++)
    { for(int c=0;c<7;c++)
      { if(map[r][c]==nullptr&&map[r+1][c]!=nullptr)
        {
            down();
        }
        }}
}
