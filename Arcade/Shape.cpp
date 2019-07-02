#include "Shape.h"

Shape::~Shape() {}

void Shape::MoveBy(const Vec2D& deltaOffset) { for (Vec2D& point : mPoints) point += deltaOffset; }
