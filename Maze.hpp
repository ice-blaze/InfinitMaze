#include <vector>

using std::vector;

class Maze
{
    private:
        vector<vector<double> > grid;
        vector<double> piece;
        double gridWidth,gridHeight;
        void deleteGrid();

        double chooseGoodPiece(double _i,double _j);

        int group0[7];
        int group1[7];
        int group2[7];
        int group3[7];

        //random groups (on pourrait les renomers groupLeft/groupUp/...
        int randGroup0();//left
        int randGroup1();//up
        int randGroup2();//right
        int randGroup3();//bottom

        int groupWallStart[3];
        int groupWallUp[4];
        int groupWallLe[4];
        int groupWallEnd[3];
        int groupWallBo[4];
        int groupWallRi[4];

        bool findNumber(int _group[],int _max, int _number);
        int randTab(int _tab[], int _max);
        int randTab(vector<int> _vec);
        int randTab(int _tab1[],int _max1,int _tab2[], int _max2);
        int randTab(int _tab1[],int _max1,int _tab2[], int _max2,int _tab3[], int _max3);

    public:

        Maze(double _gridWidth, double _gridHeight);
        ~Maze();
        void newGrid(double _gridWidth, double _gridHeight);
        const vector<vector<double> > getGrid();

        //accessor
        double getGridWidth(){return gridWidth;};
        double getGridHeight(){return gridHeight;};



};
