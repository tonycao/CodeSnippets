#include <iostream>
#include <vector>
#include <climits>

/**
* gift_wrapping algorithm to calculate convex hull
*/

typedef double REAL;

class Point{
public:
    REAL x;
    REAL y;
    Point(REAL _x, REAL _y):x(_x), y(_y){}
    Point(Point &_p) {
        this->x = _p.x;
        this->y = _p.y;
    }
    Point() {};
};

std::vector<Point> gift_wrapping(std::vector<Point>& pts)
{
    std::vector<Point> hull;

    // too little points, the original set is a "cenvex hull"
    if (pts.size() <= 3) {
        hull.insert(hull.begin(), pts.begin(), pts.end());
        return hull;
    }

    // find the first point on the convex hull, here I use the leftmost one
    static const REAL MAX_REAL = std::numeric_limits<REAL>::max();
    Point leftmost(MAX_REAL, MAX_REAL);
    for (unsigned long i = 0; i < pts.size(); ++i) {
        if (leftmost.x > pts[i].x) {
            leftmost = pts[i];
        }
    }
    hull.push_back(leftmost);

    // p0, p1, p2
    Point p0(leftmost.x, leftmost.y - 1), p1 = leftmost, p2, p_cur;
    Vector vec_left, vec_right;
    REAL max_cos = -1.1, cur_cos;

    while (true) {
        max_cos = -1.1;
        vec_left.set(p0, p1);
        for (unsigned long i = 0; i < pts.size(); ++i) {
            p_cur = pts[i];
            if (p_cur == p1) {
                continue;
            }

            vec_right.set(p1, p_cur);
            cur_cos = Vector::cosAngle(vec_left, vec_right);
            if ((cur_cos > max_cos) || (cur_cos == max_cos &&
                        ((std::fabs(vec_right.x) > (std::fabs(p2.x - p1.x))) ||
                        (std::fabs(vec_right.y) > (std::fabs(p2.y - p1.y)))))) {
                max_cos = cur_cos;
                p2 = p_cur;
            }
        }

        // convex hull found
        if (p2 == hull[0]) {
            break;
        }

        hull.push_back(p2);

        // to find next
        p0 = p1;
        p1 = p2;
    }

    return hull;
}

int main() {

}