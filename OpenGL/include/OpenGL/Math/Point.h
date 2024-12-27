#pragma once

class Point
{
public:
	Point(): m_x(0), m_y(0) {}
	Point(int m_x, int m_y): m_x(m_x), m_y(m_y) {}
	Point(const Point& point): m_x(point.m_x), m_y(point.m_y) {}
	~Point() {}

	int m_x = 0, m_y = 0;
};