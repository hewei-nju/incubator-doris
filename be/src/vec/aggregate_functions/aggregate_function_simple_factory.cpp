// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
// This file is copied from
// https://github.com/ClickHouse/ClickHouse/blob/master/src/AggregateFunctions/AggregateFunctionFactory.cpp
// and modified by Doris

#include "vec/aggregate_functions/aggregate_function_simple_factory.h"

#include "vec/aggregate_functions/aggregate_function_reader.h"

namespace doris::vectorized {

class AggregateFunctionSimpleFactory;

void register_aggregate_function_sum(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_combinator_null(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_minmax(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_avg(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_count(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_HLL_union_agg(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_uniq(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_combinator_distinct(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_bitmap(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_window_rank(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_window_lead_lag(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_stddev_variance(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_topn(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_approx_count_distinct(AggregateFunctionSimpleFactory& factory);
void register_aggregate_function_group_concat(AggregateFunctionSimpleFactory& factory);

void register_aggregate_function_percentile_approx(AggregateFunctionSimpleFactory& factory);
AggregateFunctionSimpleFactory& AggregateFunctionSimpleFactory::instance() {
    static std::once_flag oc;
    static AggregateFunctionSimpleFactory instance;
    std::call_once(oc, [&]() {
        register_aggregate_function_sum(instance);
        register_aggregate_function_minmax(instance);
        register_aggregate_function_avg(instance);
        register_aggregate_function_count(instance);
        register_aggregate_function_uniq(instance);
        register_aggregate_function_bitmap(instance);
        register_aggregate_function_combinator_distinct(instance);
        register_aggregate_function_reader(instance); // register aggregate function for agg reader
        register_aggregate_function_window_rank(instance);
        register_aggregate_function_stddev_variance(instance);
        register_aggregate_function_topn(instance);
        register_aggregate_function_approx_count_distinct(instance);
        register_aggregate_function_group_concat(instance);
        register_aggregate_function_percentile_approx(instance);

        // if you only register function with no nullable, and wants to add nullable automatically, you should place function above this line
        register_aggregate_function_combinator_null(instance);

        register_aggregate_function_reader_no_spread(instance);
        register_aggregate_function_window_lead_lag(instance);
        register_aggregate_function_HLL_union_agg(instance);
    });
    return instance;
}

} // namespace doris::vectorized