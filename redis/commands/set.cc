/*
 * Copyright (C) 2019 pengjian.uestc @ gmail.com
 */

/*
 * This file is part of Scylla.
 *
 * Scylla is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Scylla is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Scylla.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "redis/commands/set.hh"
#include "seastar/core/shared_ptr.hh"
#include "redis/request.hh"
#include "redis/reply.hh"
#include "service_permit.hh"
#include "types.hh"
#include "service/storage_proxy.hh"
#include "service/client_state.hh"
#include "redis/options.hh"
#include "redis/mutation_utils.hh"

namespace redis {

namespace commands {

shared_ptr<abstract_command> set::prepare(service::storage_proxy& proxy, request&& req)
{
    if (req.arguments_size() != 2) {
        throw wrong_arguments_exception(2, req.arguments_size(), req._command);
    }
    return seastar::make_shared<set> (std::move(req._command), std::move(req._args[0]), std::move(req._args[1]), 0);
}

future<redis_message> set::execute(service::storage_proxy& proxy, redis::redis_options& options, service_permit permit)
{
    return redis::write_strings(proxy, options, std::move(_key), std::move(_data), _ttl, permit).then([] {
        return redis_message::ok();
    });
}

}
}
