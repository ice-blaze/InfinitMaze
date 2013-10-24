#include "Maze.hpp"
#include <stdlib.h>
#include <time.h>

Maze::Maze(double _gridWidth, double _gridHeight)
{
    group0[0]=0;group0[1]=1;group0[2]=4;group0[3]=5;group0[4]=7;group0[5]=9;group0[6]=10;
    group1[0]=0;group1[1]=3;group1[2]=4;group1[3]=6;group1[4]=7;group1[5]=8;group1[6]=10;
    group2[0]=0;group2[1]=2;group2[2]=3;group2[3]=5;group2[4]=8;group2[5]=9;group2[6]=10;
    group3[0]=0;group3[1]=1;group3[2]=2;group3[3]=6;group3[4]=7;group3[5]=8;group3[6]=9;

    groupWallStart[0]=3;groupWallStart[1]=6;groupWallStart[2]=8;
    groupWallUp[0]=1;groupWallUp[1]=2;groupWallUp[2]=5;groupWallUp[3]=9;
    groupWallLe[0]=2;groupWallLe[1]=3;groupWallLe[2]=6;groupWallLe[3]=8;
    groupWallEnd[0]=1;groupWallEnd[1]=6;groupWallEnd[2]=7;
    groupWallBo[0]=3;groupWallBo[1]=4;groupWallBo[2]=5;groupWallBo[3]=10;
    groupWallRi[0]=1;groupWallRi[1]=4;groupWallRi[2]=6;groupWallRi[3]=7;

    srand ( time(NULL) );
    gridWidth=gridHeight=0;
    newGrid(_gridWidth, _gridHeight);
}

Maze::~Maze()
{
    deleteGrid();
    gridHeight=gridWidth=0;
}

void Maze::newGrid(double _gridWidth, double _gridHeight)
{
    //supprime la grille avant de faire la nouvelle sauf s'il y en a aucune
    if(gridHeight>0&&gridWidth>0)
        deleteGrid();


    gridWidth=_gridWidth;
    gridHeight=_gridHeight;

    //création de la grille
    for ( double i = 0; i < gridWidth; i++ )
    {
        grid.push_back ( vector<double>() );
        for ( double j = 0; j < gridHeight; j++ )
            grid[i].push_back (chooseGoodPiece(i,j));
    }
}

void Maze::deleteGrid()
{
    //supprime la grille
    for ( double i = gridWidth; i > 0; i-- )
    {
        for ( double j = gridHeight; j > 0; j-- )
            grid[i].pop_back ();
        grid.pop_back ();
    }
}

//retourne juste le vecteur
const vector<vector<double> > Maze::getGrid()
{
    return grid;
}

//{region start


//}

double Maze::chooseGoodPiece(double _i,double _j)
{
    double i=_i,j=_j;
    if(i==0&&j==0)
    {
        return randTab(groupWallStart,3);
    }
    else if(i==0&&j!=gridWidth-1)//haut bloquer
    {
        if(findNumber(group2,7,(int)grid[i][j-1]))
        {
            int result=2;
            while(result==2)
                result = randTab(groupWallUp,4);
            return result;
        }
        else
            return 2;
    }
    else if(i==0&&j==gridWidth-1)//coin haut gauche
    {
        if(findNumber(group2,7,(int)grid[i][j-1]))
            return 1;
        else
            return -1;
    }
    else if(i<gridHeight-1&&j==0)//colonne drote
    {
//        if(findNumber(group2,7,(int)grid[i-1][j]))//il faudrait mettre grid en int plutot qu'en double
//            return 0;
        if(findNumber(group3,7,(int)grid[i-1][j]))
        {
            int result=2;
            while (result==2)
                result = randTab(groupWallLe,4);
            return result;
        }
        else
            return 2;
    }
    else if(i==gridHeight-1&&j==0)//bas gauche
    {
        if(findNumber(group3,7,(int)grid[i-1][j]))
            return 3;
        else
            return -1;
    }
    else if(i>0&&i<gridHeight-1&&j>0&&j<gridWidth-1)//case millieu
    {
        if(findNumber(group3,7,(int)grid[i-1][j])&&findNumber(group2,7,(int)grid[i][j-1]))
        {
            return randTab(group0,7,group1,7);
        }
        else if (findNumber(group3,7,(int)grid[i-1][j])&&!findNumber(group2,7,(int)grid[i][j-1]))
        {
            int result = 2;
            while (result==2)
                result = randTab(groupWallLe,4);

            return result;
        }
        else if (!findNumber(group3,7,(int)grid[i-1][j])&&findNumber(group2,7,(int)grid[i][j-1]))
        {
            int result=2;
            while(result==2)
                result = randTab(groupWallUp,4);
            return result;
        }
        else
            return 2;
    }
    else if(i>0&&i<gridHeight-1&&j==gridWidth-1)//colonne à droite
    {
        if(findNumber(group3,7,(int)grid[i-1][j])&&findNumber(group2,7,(int)grid[i][j-1]))
        {
            return randTab(group0,7,group1,7,groupWallRi,4);
        }
        else if(!findNumber(group3,7,(int)grid[i-1][j])&&findNumber(group2,7,(int)grid[i][j-1]))
        {
            return randTab(group0,7,groupWallUp,4,groupWallRi,4);
        }
        else if(findNumber(group3,7,(int)grid[i-1][j])&&!findNumber(group2,7,(int)grid[i][j-1]))
        {
            return 6;
        }
    }
    else if (i==gridHeight-1&&j>0&&j<gridWidth-1)//ligne en bas
    {
        if(findNumber(group3,7,(int)grid[i-1][j])&&findNumber(group2,7,(int)grid[i][j-1]))
        {
            return randTab(group0,7,group1,7,groupWallBo,4);
        }
        else if(!findNumber(group3,7,(int)grid[i-1][j])&&findNumber(group2,7,(int)grid[i][j-1]))
        {
            return randTab(group0,7,groupWallUp,4,groupWallBo,4);
        }
        else if(findNumber(group3,7,(int)grid[i-1][j])&&!findNumber(group2,7,(int)grid[i][j-1]))
        {
            return 3;
        }
    }
    //else if()//bas droit end
    return -1;
}

bool Maze::findNumber(int _group[],int _max,int _number)
{
    for (int i=0;i<_max;i++)
    {
        if(_group[i]==_number)
            return true;
    }
    return false;
}

int Maze::randTab(int _tab[], int _max)
{
    return _tab[rand() % _max];
}

int Maze::randTab(vector<int> _vec)
{
    return _vec[rand() % _vec.size()];
}

//je mets toutes les possibilité dans un tableau(gauche/haut/droite/bas) et je sorts un nombre au pif
int Maze::randGroup0()
{
    return group0[rand() % 7];//rand de 0 à 7
}

int Maze::randGroup1()
{
    return group1[rand() % 7];//rand de 0 à 7
}

int Maze::randGroup2()
{
    return group2[rand() % 7];//rand de 0 à 7
}

int Maze::randGroup3()
{
    return group3[rand() % 7];//rand de 0 à 7
}



int Maze::randTab(int _tab1[],int _max1,int _tab2[], int _max2)
{
    vector<int> fusionTab;

    for (int i=0;i<_max1;i++)
    {
        for (int j=0;j<_max2;j++)
        {
        	if(_tab1[i]==_tab2[j])
        	{
        	    fusionTab.push_back(_tab1[i]);
        	}
        }
    }

    return randTab(fusionTab);
}

int Maze::randTab(int _tab1[],int _max1,int _tab2[], int _max2,int _tab3[], int _max3)
{
    vector<int> fusionTab;

    for (int i=0;i<_max1;i++)
    {
        for (int j=0;j<_max2;j++)
        {
            for (int k=0;k<_max3;k++)
            {
                if(_tab1[i]==_tab2[j]&&_tab1[i]==_tab3[k]&&_tab2[j]==_tab3[k])
                {
                    fusionTab.push_back(_tab1[i]);
                }
            }
        }
    }

    return randTab(fusionTab);
}

