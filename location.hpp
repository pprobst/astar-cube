#ifndef _LOCATIONH_
#define _LOCATIONH_

#include "libs.hpp"

/**
 * A point in 3D space.
 */
struct Point {
    int x, y, z;
};

/**
 * Print coordinates in a pretty way.
 */
inline ostream& operator<<(std::ostream& os, const Point& pt) {
    return os << "(" << pt.x << ", " << pt.y << ", " << pt.z << ")";
}

class Location {
    private:
        Point point; // (X, Y, Z)
        bool blocker; // Is this location not passable?

    public:
        Location(int x, int y, int z);
        Location();

        void setBlocker();

        void setPoint(int x, int y, int z);

        Point getPoint() const;

        int getX() const;

        int getY() const;

        int getZ() const;

        /*
         * Transforms a 3D point to an index in a 1D array.
         */
        int toIndex(int height, int width);

        bool isBlocker() const;

        /*
         * Lots of operator overrides!
         */
        inline bool operator==(const Location &rhs) const {
            return (this->getX() == rhs.getX() && this->getY() == rhs.getY() && this->getZ() == rhs.getZ());
        }

        inline bool operator!=(const Location &rhs) const {
            return !(this->operator==(rhs));
        }

        inline Location operator+(const Location &rhs) const {
            return Location(this->getX() + rhs.getX(), this->getY() + rhs.getY(), this->getZ() + rhs.getZ());
        }

        inline Location operator-(const Location &rhs) const {
            return Location(this->getX() - rhs.getX(), this->getY() - rhs.getY(), this->getZ() - rhs.getZ());
        }

        inline Location& operator+=(const Location &rhs) {
            this->setPoint(this->getX() + rhs.getX(), this->getY() + rhs.getY(), this->getZ() + rhs.getZ());
            return *this;
        }

        inline Location& operator-=(const Location &rhs) {
            this->setPoint(this->getX() - rhs.getX(), this->getY() - rhs.getY(), this->getZ() - rhs.getZ());
            return *this;
        }

        inline bool operator<(const Location &rhs) const {
            return (tie(this->point.x, this->point.y, this->point.z) < tie(rhs.point.x, rhs.point.y, rhs.point.z));
        }
};

/*
 * We need to define a hash so that a Location may be inserted in an
 * unordered map (which is like a Python dict).
 */
namespace std {
    template<> struct hash<Location> {
        typedef Location argument_type;
        typedef size_t result_type;
        size_t operator()(const Location& id) const noexcept {
            size_t res = 17;
            res = res * 31 + hash<int>()( id.getX() );
            res = res * 31 + hash<int>()( id.getY() );
            res = res * 31 + hash<int>()( id.getZ() );
            return res;
        }
    };
}

inline ostream& operator<<(ostream &os, const Location &rhs) {
    return os << rhs.getPoint();
}

#endif
