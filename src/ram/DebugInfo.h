/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file DebugInfo.h
 *
 ***********************************************************************/

#pragma once

#include "ram/AbstractLog.h"
#include "ram/Node.h"
#include "ram/NodeMapper.h"
#include "ram/Statement.h"
#include "souffle/utility/MiscUtil.h"
#include "souffle/utility/StreamUtil.h"
#include "souffle/utility/StringUtil.h"
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace souffle::ram {

/**
 * @class DebugInfo
 * @brief Debug statement
 *
 * For example:
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * BEGIN_DEBUG "gen(1) \nin file /file.dl [7:7-7:10]\;"
 *   ...
 * END_DEBUG
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
class DebugInfo : public Statement, public AbstractLog {
public:
    DebugInfo(Own<Statement> stmt, std::string msg) : AbstractLog(std::move(stmt), std::move(msg)) {}

    std::vector<const Node*> getChildNodes() const override {
        return AbstractLog::getChildNodes();
    }

    DebugInfo* clone() const override {
        return new DebugInfo(souffle::clone(statement), message);
    }

    void apply(const NodeMapper& map) override {
        AbstractLog::apply(map);
    }

protected:
    void print(std::ostream& os, int tabpos) const override {
        os << times(" ", tabpos) << "BEGIN_DEBUG \"" << stringify(message) << "\"" << std::endl;
        Statement::print(statement.get(), os, tabpos + 1);
        os << times(" ", tabpos) << "END_DEBUG" << std::endl;
    }
};

}  // namespace souffle::ram
