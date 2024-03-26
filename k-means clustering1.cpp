#include <bits/stdc++.h>
using namespace std;

vector<pair<float, float>> points {};
vector<pair<float, float>> clusters {};

vector<vector<pair<float, float>>> groups;

void input_points(int n)
{
    float f1, f2;
    cout << "Enter the coordinates of the points: " << "\n";
    for (int i = 0; i < n; i++)
    {
        cin >> f1 >> f2;
        cout << "\n";
        if (!(f1 < -180 || f1 > 180 || f2 < -180 || f2 > 180))
        {
            points.push_back({f1, f2});
            for (auto j : points)
            {
                cout << j.first << " " << j.second << "\n";
            }
        }
        else
        {
            cout << "Invalid coordinates! Please enter again:" << endl;
            i--;
        }
    }
}

void input_clusters(int n)
{
    float f1, f2;
    cout << "Enter the coordinates of the clusters: " << "\n";
    for (int i = 0; i < n; i++)
    {
        cin >> f1 >> f2;
        cout << "\n";
        if (!(f1 < -180 || f1 > 180 || f2 < -180 || f2 > 180))
        {
            clusters.push_back({f1, f2});
            for (auto j : clusters)
            {
                cout << j.first << " " << j.second << "\n";
            }
        }
        else
        {
            cout << "Invalid coordinates! Please enter again:" << endl;
            i--;
        }
    }
    groups.resize(clusters.size());
}

void kmeans()
{
    bool hasChanged = true;
    const int maxIterations = 100;
    int iteration = 0;
    while (hasChanged && iteration < maxIterations)
    {
        hasChanged = false;

        for (auto& group : groups)
        {
            group.clear();
        }

        for (auto i : points)
        {
            float lastDist = FLT_MAX;
            int cCI = -1;
            int idx = 0;

            for (auto j : clusters)
            {
                float dist = sqrt(pow(i.first - j.first, 2) + pow(i.second - j.second, 2));
                if (dist < lastDist)
                {
                    lastDist = dist;
                    cCI = idx;
                }
                idx++;
            }
            if (cCI != -1)
            {
                groups[cCI].push_back(i);
            }
        }

        for (int i = 0; i < clusters.size(); i++)
        {
            float sumX = 0.0, sumY = 0.0;
            int count = 0;

            for (auto point : groups[i])
            {
                sumX += point.first;
                sumY += point.second;
                count++;
            }

            if (count > 0) 
            {
                float newX = sumX / count;
                float newY = sumY / count;

                if (clusters[i].first != newX || clusters[i].second != newY)
                {
                    hasChanged = true;
                    clusters[i].first = newX;
                    clusters[i].second = newY;
                }
            }
        }
        iteration++;
    } 
} 

int main() 
{
    int Pnum, Cnum;
    
    cout << "Enter the number of points: " << "\n";
    cin >> Pnum;
    input_points(Pnum);

    cout << "Enter the number of clusters: " << "\n";
    cin >> Cnum;
    input_clusters(Cnum);

    kmeans();

    cout << "The points are grouped into the following clusters: " << "\n";
    for (int i = 0; i < groups.size(); i++) {
        cout << "Cluster " << i << ": ";
        for (auto j : groups[i]) {
            cout << "(" << j.first << ", " << j.second << ") ";
        }
        cout << "\n";
    }
    
    return 0;
}
