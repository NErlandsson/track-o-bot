#pragma once

#include "Hearthstone.h"
#include "HearthstoneLogTracker.h"
#include "Result.h"
#include "ResultQueue.h"

#include "RankClassifier.h"

#include <QTimer>
#include <QTime>

#include <vector>

class Core : public QObject
{
  Q_OBJECT

private:
  QTimer*               mTimer;
  bool                  mGameRunning;
  HearthstoneLogTracker mLogTracker;
  QTime                 mDurationTimer;

  Result                mResult;
  std::vector<int>      mRanks;

  RankClassifier        mRankClassifier;

  ResultQueue           mResultsQueue;

  void ResetResult();
  void UploadResult();

  int DetermineRank();

  bool mGameClientRestartRequired;
  void SetGameClientRestartRequired( bool restartRequired );

private slots:
  void HandleMatchStart();
  void HandleMatchEnd( const ::CardHistoryList& cardHistoryList, bool wasSpectating );

  void HandleOutcome( Outcome outcome );
  void HandleOwnClass( Class ownClass );
  void HandleOpponentClass( Class opponentClass );
  void HandleOrder( GoingOrder order );
  void HandleGameMode( GameMode mode );
  void HandleTurn( int turn, bool ownTurn );
  void HandleLegend( int legend );

  void Tick();

signals:
  void HandleGameClientRestartRequired( bool restartRequired );

public:

  Core();
  ~Core();
};
