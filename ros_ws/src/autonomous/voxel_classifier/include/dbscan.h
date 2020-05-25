// Von https://github.com/james-yoo/DBSCAN geklaut

#ifndef DBSCAN_H
#define DBSCAN_H

#include <cmath>
#include <vector>

#define UNCLASSIFIED -1
#define CORE_POINT 1
#define BORDER_POINT 2
#define NOISE -2
#define SUCCESS 0
#define FAILURE -3

using namespace std;

typedef struct Point_
{
    float x, y, z, r, g, b; // X, Y, Z position
    int clusterID;          // clustered ID
} Point;

class DBSCAN
{
    public:
    DBSCAN(unsigned int minPts, float eps, vector<Point_>* points)
    {
        m_minPoints = minPts;
        m_epsilon = eps;
        m_points = points;
        m_pointSize = points->size();
    }
    ~DBSCAN()
    {
    }

    int run();
    vector<int> calculateCluster(Point_ point);
    int expandCluster(Point_ point, int clusterID);
    inline double calculateDistance(Point_ pointCore, Point_ pointTarget);

    int getTotalPointSize()
    {
        return m_pointSize;
    }
    int getMinimumClusterSize()
    {
        return m_minPoints;
    }
    int getEpsilonSize()
    {
        return m_epsilon;
    }

    private:
    vector<Point_>* m_points;
    unsigned int m_pointSize;
    unsigned int m_minPoints;
    float m_epsilon;
};

#endif // DBSCAN_H
