//
//  Play.h
// 1、判断消除的是那种颜色，让宠物前进
// 2、判断宠物是否能攻击怪兽了
// 3、宝石被消除后也会攻击怪兽，3消4消5消等攻击的血量不同
// 4、记得宝石下落后再判定有没有可消除的
// 5、最最最最重要的：读取棋盘信息是从本地的一个文件读取的，什么文件，文件什么格式看你喜欢
// 6、可添加消除的时候的效果，但不是重点
// 7、去试试那个游戏就明白了
//
//

#ifndef __ttgame__PlayScene__
#define __ttgame__PlayScene__
#include "cocos2d.h"
#include "DiamondSprite.h"
using namespace cocos2d;
enum class GAMEDIR{
 DIR_UP,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_DOWN
};
class Play:public Layer{
public:
    CREATE_FUNC(Play);
    static Scene * createScene(int level,int pet);
    bool init();
    int startX,startY;
    DiamondSprite * map[7][7];//7行7列的数组
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    void moveDiamondSprite(GAMEDIR d,int r,int c);
    bool removeDiamondSprite();//消除卡片
    void autoDownDiamondSprite();//自动掉落
    void down();//落下
};
#endif /* defined(__ttgame__Play__) */
