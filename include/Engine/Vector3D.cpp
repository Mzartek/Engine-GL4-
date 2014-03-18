template <typename T>
engine::Vector3D<T>::Vector3D(void)
{
  _x=0;
  _y=0;
  _z=0;
  _px=&_x;
  _py=&_y;
  _pz=&_z;
}

template <typename T>
engine::Vector3D<T>::Vector3D(T const &x, T const &y, T const &z)
{
  _x=x;
  _y=y;
  _z=z;
  _px=&_x;
  _py=&_y;
  _pz=&_z;
}

template <typename T>
engine::Vector3D<T>::~Vector3D(void)
{
}

template <typename T>
void engine::Vector3D<T>::changement(T const &x, T const &y, T const &z)
{
  _x = x;
  _y = y;
  _z = z;
}

template <typename T>
void engine::Vector3D<T>::operator=(Vector3D<T> const &v)
{
  _x = v._x;
  _y = v._y;
  _z = v._z;
}

template <typename T>
void engine::Vector3D<T>::operator+=(Vector3D<T> const &v)
{
  _x += v._x;
  _y += v._y;
  _z += v._z;
}

template <typename T>
void engine::Vector3D<T>::operator-=(Vector3D<T> const &v)
{
  _x -= v._x;
  _y -= v._y;
  _z -= v._z;
}

template <typename T>
void engine::Vector3D<T>::operator*=(Vector3D<T> const &v)
{
  _x *= v._x;
  _y *= v._y;
  _z *= v._z;
}

template <typename T>
void engine::Vector3D<T>::operator/=(Vector3D<T> const &v)
{
  _x /= v._x;
  _y /= v._y;
  _z /= v._z;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator+(Vector3D<T> const &v) const
{
  Vector3D<T> t = *this;
  t += v;
  return t;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator-(Vector3D<T> const &v) const
{
  Vector3D<T> t = *this;
  t -= v;
  return t;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator*(Vector3D<T> const &v) const
{
  Vector3D<T> t = *this;
  t *= v;
  return t;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator/(Vector3D<T> const &v) const
{
  Vector3D<T> t = *this;
  t /= v;
  return t;
}

template <typename T>
void engine::Vector3D<T>::operator=(T const &n)
{
  _x = n;
  _y = n;
  _z = n;
}

template <typename T>
void engine::Vector3D<T>::operator+=(T const &n)
{
  _x += n;
  _y += n;
  _z += n;
}

template <typename T>
void engine::Vector3D<T>::operator-=(T const &n)
{
  _x -= n;
  _y -= n;
  _z -= n;
}

template <typename T>
void engine::Vector3D<T>::operator*=(T const &n)
{
  _x *= n;
  _y *= n;
  _z *= n;
}

template <typename T>
void engine::Vector3D<T>::operator/=(const T &n)
{
  _x /= n;
  _y /= n;
  _z /= n;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator+(T const &n) const
{
  Vector3D<T> t = *this;
  t += n;
  return t;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator-(T const &n) const
{
  Vector3D<T> t = *this;
  t -= n;
  return t;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator*(T const &n) const
{
  Vector3D<T> t = *this;
  t *= n;
  return t;
}

template <typename T>
engine::Vector3D<T> engine::Vector3D<T>::operator/(T const &n) const
{
  Vector3D<T> t = *this;
  t /= n;
  return t;
}
