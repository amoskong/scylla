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

#pragma once

#include "redis/request.hh"
#include "redis/abstract_command.hh"

namespace redis {

namespace commands {

class unknown : public abstract_command {
public:
    static shared_ptr<abstract_command> prepare(service::storage_proxy& proxy, request&& req);
    
    unknown(bytes&& name) : abstract_command(std::move(name))
    {
    }

    ~unknown()
    {
    }
    
    future<redis_message> execute(service::storage_proxy&, redis_options&, service_permit permit) override;
};
/*
class unexpected : public abstract_command {
public:
    static shared_ptr<abstract_command> prepare(service::storage_proxy& proxy, const service::client_state& cs, request&& req);
    
    unexpected(bytes&& name, bytes&& message) : abstract_command(std::move(name))
    {
    }

    ~unexpected()
    {
    }
    
    future<redis_message> execute(service::storage_proxy&, service::client_state&, redis_options&) override;
};
*/
}
}
