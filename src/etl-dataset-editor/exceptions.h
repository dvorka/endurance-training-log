/*
 exceptions.h     Endurance Training Log dataset editor

 Copyright (C) 2020 Martin Dvorak <martin.dvorak@mindforger.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef ETL76_EXCEPTIONS_H
#define ETL76_EXCEPTIONS_H

#include <exception>
#include <string>

namespace etl76 {

class EtlException : public std::exception
{
private:
    const std::string message;

public:
    explicit EtlException(const std::string& message) throw()
        : message(message) {}

    const char* what() const throw() { return message.c_str(); }
};

/**
 * @brief User exception.
 *
 * User exception is caused by user configuration errors and can be fixed by users.
 * This needs a very clear explanation of what the user did wrong and how to fix it.
 */
class EtlUserException : public EtlException
{
public:
    explicit EtlUserException(const std::string& message) throw()
        : EtlException(message) {}
};

/**
 * @brief Runtime exception.
 *
 * Runtime exception is caused by the system configuration/system state error and
 * can be handled by a fallback or user action.
 */
class EtlRuntimeException : public EtlException
{
public:
    explicit EtlRuntimeException(const std::string& message) throw()
        : EtlException(message) {}
};

/**
 * @brief Error.
 *
 * Errors should not happen and can only be fixed by programmers ~ is an implementation
 * error. Error should *never* be caught.
 */
class EtlError: public EtlException
{
public:
    explicit EtlError(const std::string& message) throw()
        : EtlException(message) {}
};

} // namespace etl76

#endif // ETL76_EXCEPTIONS
