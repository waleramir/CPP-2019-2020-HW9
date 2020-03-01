#ifndef FILESYSTEMCLASSES_H
#define FILESYSTEMCLASSES_H
#include <QFileDialog>
#include <QDebug>

class IPrintable
{
public:
  virtual ~IPrintable() = default;
  virtual QString Print() = 0;
};

class IHavePath
{
public:
  virtual ~IHavePath() = default;
  virtual void SetPath(QString path) = 0;
};

class File : public IPrintable, public IHavePath
{
  QFile _file;

public:
  void SetPath(QString filepath) override;
  QString Print() override;
};

class Directory : public IPrintable, public IHavePath
{
  QDir _dir;

public:
  void SetPath(QString dirpath) override;
  QString Print() override;
};

enum class SelectFileMode
{
  Static = -2,
  Custom = -3
};

#endif  // FILESYSTEMCLASSES_H
