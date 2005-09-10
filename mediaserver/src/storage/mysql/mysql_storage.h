/*  Mysql_storage.h - this file is part of MediaTomb.

    Copyright (C) 2005 Gena Batyan <bgeradz@deadlock.dhs.org>,
                       Sergey Bostandzhyan <jin@deadlock.dhs.org>

    MediaTomb is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    MediaTomb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MediaTomb; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __MYSQL_STORAGE_H__
#define __MYSQL_STORAGE_H__

#include "common.h"
#include "storage/sql_storage.h"

#include <mysql.h>
#include <pthread.h>

class MysqlRow : public SQLRow
{
public:
    MysqlRow(MYSQL_ROW mysql_row);
    virtual zmm::String col(int index);
protected:
    MYSQL_ROW mysql_row;
};

class MysqlResult : public SQLResult
{
    int nullRead;
public:
    MysqlResult(MYSQL_RES *mysql_res);
    virtual ~MysqlResult();
    virtual zmm::Ref<SQLRow> nextRow();
protected:
    MYSQL_RES *mysql_res;
};

class MysqlStorage : public SQLStorage
{
public:
    MysqlStorage();
    virtual ~MysqlStorage();

    virtual void init();
    virtual zmm::String quote(zmm::String str);
    virtual zmm::Ref<SQLResult> select(zmm::String query);
    virtual void exec(zmm::String query);
    virtual int lastInsertID();

protected:
    MYSQL *db;
    pthread_mutex_t lock_mutex;

    void reportError(zmm::String query);

    void lock();
    void unlock();    
    
    friend void unlock_func(void *data);    
};


#endif // __MYSQL_STORAGE_H__

