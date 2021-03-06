//=============================================================================
//
// 数字を管理するよ [CNumberManager.h]
//
// Auther : masato masuda
//
//=============================================================================

//=============================================================================
// include guard
//=============================================================================
#ifndef _NUMBER_MANAGER_H_
#define _NUMBER_MANAGER_H_

//=============================================================================
// include
//=============================================================================
#include "main.h"
#include "Polygon2D.h"

class CNumber2D;

//=============================================================================
// class
//=============================================================================
class CNumberManager :public CPolygon2D
{
public:

  // 数字の種類
  typedef enum _TYPE{
    TYPE_PLAYER_01,
    TYPE_PLAYER_02,
    TYPE_PLAYER_03,
    TYPE_PLAYER_04,
    TYPE_PLAYER_05,
    TYPE_PLAYER_06,
    TYPE_MAX
  } TYPE;

  static const int NUMBER_MAX = 6;
  static const int FIGURE_MAX = 2;
  typedef struct _NUMBER{
    CNumber2D*  _kill[FIGURE_MAX];    // KILLを桁数分
    CNumber2D*  _death[FIGURE_MAX];   // DEATHを桁数分
  } NUMBER;

  CNumberManager();
  ~CNumberManager(){}

  void Init(void);
  void Update(void);
  void Draw(void){}

  // Create
  static CNumberManager* Create();

  // 数値を設定
  void SetNumberKill(TYPE type, int kill);
  void SetNumberDeath(TYPE type, int death);
  void SetNumber(TYPE type, int kill, int death);

  // Geter / Seter
  void SetDrawFlag(bool flag);

private:

  bool    drawFlag;
  NUMBER  number[NUMBER_MAX];

};

#endif

// end of file