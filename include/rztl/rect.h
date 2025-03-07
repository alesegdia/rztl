#pragma once

namespace rztl {

    template <typename T>
    class Rect {
    private:
        T mX;
        T mY;
        T mWidth;
        T mHeight;

    public:
        // Default constructor
        Rect() : mX(0), mY(0), mWidth(0), mHeight(0) {}

        // Parameterized constructor
        Rect(T x, T y, T width, T height) : mX(x), mY(y), mWidth(width), mHeight(height) {}

        // Copy constructor
        Rect(const Rect& other) : mX(other.mX), mY(other.mY), mWidth(other.mWidth), mHeight(other.mHeight) {}

        // Assignment operator
        Rect& operator=(const Rect& other) {
            if (this != &other) {
                mX = other.mX;
                mY = other.mY;
                mWidth = other.mWidth;
                mHeight = other.mHeight;
            }
            return *this;
        }

        // Destructor
        ~Rect() {}

        // Getters
        T GetX() const { return mX; }
        T GetY() const { return mY; }
        T GetWidth() const { return mWidth; }
        T GetHeight() const { return mHeight; }

        // Setters
        void SetX(T x) { mX = x; }
        void SetY(T y) { mY = y; }
        void SetWidth(T width) { mWidth = width; }
        void SetHeight(T height) { mHeight = height; }

        // Method to calculate the area of the rectangle
        T Area() const {
            return mWidth * mHeight;
        }

        // Method to check if a point is inside the rectangle
        bool Contains(T px, T py) const {
            return (px >= mX && px <= mX + mWidth && py >= mY && py <= mY + mHeight);
        }

        // Method to check if this rectangle intersects with another rectangle
        bool Intersects(const Rect& other) const {
            return !(mX > other.mX + other.mWidth || mX + mWidth < other.mX || mY > other.mY + other.mHeight || mY + mHeight < other.mY);
        }

        // Method to calculate the depths of another rectangle inside this rectangle
        void Depth(const Rect& other, T& leftDepth, T& rightDepth, T& topDepth, T& bottomDepth) const {
            leftDepth = other.mX - mX;
            rightDepth = (mX + mWidth) - (other.mX + other.mWidth);
            topDepth = other.mY - mY;
            bottomDepth = (mY + mHeight) - (other.mY + other.mHeight);
        }
    };

}