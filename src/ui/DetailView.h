//
//          Copyright (c) 2016, Scientific Toolworks, Inc.
//
// This software is licensed under the MIT License. The LICENSE.md file
// describes the conditions under which this software may be distributed.
//
// Author: Jason Haslam
//

#ifndef DETAILVIEW_H
#define DETAILVIEW_H

#include "RepoView.h"
#include <QWidget>

class QStackedWidget;

namespace git {
class Diff;
class Index;
class Repository;
}

// Abstract interface for content widgets.
class ContentWidget : public QWidget
{
public:
  ContentWidget(QWidget *parent = nullptr);
  virtual ~ContentWidget();

  virtual QString selectedFile() const = 0;
  virtual QModelIndex selectedIndex() const = 0;

  virtual void setDiff(
    const git::Diff &diff,
    const QString &file = QString(),
    const QString &pathspec = QString()) = 0;

  virtual void cancelBackgroundTasks() {}

  virtual void find() {}
  virtual void findNext() {}
  virtual void findPrevious() {}
};

class DetailView : public QWidget
{
  Q_OBJECT

public:
  DetailView(const git::Repository &repo, QWidget *parent = nullptr);
  virtual ~DetailView();

  // commit
  void commit();
  bool isCommitEnabled() const;

  // stage / unstage
  void stage();
  bool isStageEnabled() const;
  void unstage();
  bool isUnstageEnabled() const;

  // mode
  RepoView::ViewMode viewMode() const;
  void setViewMode(RepoView::ViewMode mode, bool spontaneous);

  QString file() const;

  void setCommitMessage(const QString &message);
  void setDiff(
    const git::Diff &diff,
    const QString &file = QString(),
    const QString &pathspec = QString());

  void cancelBackgroundTasks();

  void find();
  void findNext();
  void findPrevious();

signals:
  void viewModeChanged(RepoView::ViewMode mode, bool spontaneous = false);

private:
  enum DetailIndex
  {
    CommitIndex,
    EditorIndex
  };

  enum ContentIndex
  {
    DiffIndex,
    TreeIndex
  };

  QStackedWidget *mDetail;
  QStackedWidget *mContent;
};

#endif
