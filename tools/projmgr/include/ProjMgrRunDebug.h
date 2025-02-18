/*
 * Copyright (c) 2024 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PROJMGRRUNDEBUG_H
#define PROJMGRRUNDEBUG_H

#include "ProjMgrWorker.h"

 /**
  * @brief programming algorithm types
 */
struct AlgorithmType {
  std::string algorithm;
  unsigned long long start = 0;
  unsigned long long size = 0;
  unsigned long long ramStart = 0;
  unsigned long long ramSize = 0;
  bool bDefault = false;
};

/**
 * @brief files type
*/
struct FilesType {
  std::string file;
  std::string type;
};

/**
 * @brief debug sequences block type
*/
struct DebugSequencesBlockType {
  std::string info;
  std::string execute;
  std::string control_if;
  std::string control_while;
  std::string timeout;
  bool atomic;
  std::vector<DebugSequencesBlockType> blocks;
};

/**
 * @brief debug sequences type
*/
struct DebugSequencesType {
  std::string name;
  std::string info;
  std::vector<DebugSequencesBlockType> blocks;
};

 /**
  * @brief debug run manager types
 */
struct RunDebugType {
  std::string solution;
  std::string targetType;
  std::string compiler;
  std::string board;
  std::string boardPack;
  std::string device;
  std::string devicePack;
  std::vector<AlgorithmType> algorithms;
  std::vector<FilesType> outputs;
  std::vector<FilesType> systemDescriptions;
  std::vector<DebugSequencesType> debugSequences;
};

/**
  * @brief projmgr run debug management class
*/
class ProjMgrRunDebug {
public:
  /**
   * @brief class constructor
  */
  ProjMgrRunDebug(void);

  /**
   * @brief class destructor
  */
  ~ProjMgrRunDebug(void);

  /**
   * @brief get run debug info
   * @return reference to m_runDebug
  */
  RunDebugType& Get() { return m_runDebug; };

  /**
   * @brief collect run/debug info for selected contexts
   * @param vector of selected contexts
   * @return true if executed successfully
  */
  bool CollectSettings(const std::vector<ContextItem*>& contexts);

protected:
  RunDebugType m_runDebug;
  void GetDebugSequenceBlock(const RteItem* item, DebugSequencesBlockType& block);
};

#endif  // PROJMGRRUNDEBUG_H
