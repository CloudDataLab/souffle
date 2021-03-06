/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file EmptinessCheck.h
 *
 * Defines a class for evaluating conditions in the Relational Algebra
 * Machine.
 *
 ***********************************************************************/

#pragma once

#include "ram/Condition.h"
#include "ram/Node.h"
#include "ram/NodeMapper.h"
#include "ram/Relation.h"
#include "souffle/utility/ContainerUtil.h"
#include "souffle/utility/MiscUtil.h"
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace souffle::ram {

/**
 * @class EmptinessCheck
 * @brief Emptiness check for a relation
 *
 * Evaluates to true if the given relation is the empty set
 *
 * For example:
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * (B = ∅)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
class EmptinessCheck : public Condition {
public:
    EmptinessCheck(Own<RelationReference> relRef) : relationRef(std::move(relRef)) {
        assert(relationRef != nullptr && "Relation reference is a nullptr");
    }

    /** @brief Get relation */
    const Relation& getRelation() const {
        return *relationRef->get();
    }

    std::vector<const Node*> getChildNodes() const override {
        return {relationRef.get()};
    }

    EmptinessCheck* clone() const override {
        return new EmptinessCheck(souffle::clone(relationRef));
    }

    void apply(const NodeMapper& map) override {
        relationRef = map(std::move(relationRef));
    }

protected:
    void print(std::ostream& os) const override {
        os << "(" << getRelation().getName() << " = ∅)";
    }

    bool equal(const Node& node) const override {
        const auto& other = static_cast<const EmptinessCheck&>(node);
        return equal_ptr(relationRef, other.relationRef);
    }

    /** Relation */
    Own<RelationReference> relationRef;
};

}  // namespace souffle::ram
