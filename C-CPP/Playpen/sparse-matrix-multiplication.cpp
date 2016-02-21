
unordered_map<pair<int, int>, int> add(unordered_map<pair<int, int>, int> a, unordered_map<pair<int, int>, int> b)
{
    unordered_map<pair<int, int>, int> result;

    for (auto point : a) 
    {
        if (b.find(point.first) != b.end())
            result[point.first] = a[point.first] + b[point.first];
        else
            result[point.first] = a[point.first];
    }

    for (auto point : b)
    {
        if (a.find(point.first) == a.end())
            result[point.first] = b[point.first];
    }

    return result;
};

unordered_map<pair<int, int>, int> multiply(unordered_map<pair<int, int>, int> a, unordered_map<pair<int, int>, int> b)
{
    unordered_map<pair<int, int>, int> result;
    for (auto pointA : a)
        for (auto pointB : b)
        {
            if (pointA.first.second == pointB.first.first)
            {
                int num = pointA.second * pointB.second;
                int row = pointA.first.first;
                int col = pointB.first.second;
                if (result.find(make_pair(row, col)) != result.end())
                    result[make_pair(row, col)] += num;
                else
                    result[make_pair(row, col)] = num;
            }
        }
};