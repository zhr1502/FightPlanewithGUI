#define TableSiz 1.0
#define OrdinarySiz 0.87
#define SelectedSiz 0.95
#define MapW 10
#define MapH 10
#define TopBarSiz 1.0
#define EdgeSiz 0.5
#define MiddleSiz 0.5
#define BottomBarSiz 1.5
#define WidthSizeinAxis (MapW*TableSiz*2+EdgeSiz*2+MiddleSiz)
#define HeightSizeinAxis ((float)MapH*TableSiz+TopBarSiz+BottomBarSiz)
#define BottomAxis (-MapH*TopBarSiz/2-BottomBarSiz)
#define TopAxis (MapH*TopBarSiz/2+TopBarSiz)
#define LeftEdgeAxis (-WidthSizeinAxis/2)
#define RightEdgeAxis (WidthSizeinAxis/2)

