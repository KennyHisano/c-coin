//
//  util.h
//  c++coin
//
//  Created by NandN on 2017/09/16.
//  Copyright © 2017 NandN. All rights reserved.
//


#include "fs.h"
#include "sync.h"
#include "tinyformat.h"



#include <atomic>
#include <exception>
#include <map>
#include <stdint.h>
#include <string>
#include <vector>

#include <boost/signals2/signal.hpp>
#include <boost/thread/exceptions.hpp>

fs::path GetDefaultDataDir();
const fs::path &GetDataDir(bool fNetSpecific = true);



class ArgsManager
{
protected:
    CCriticalSection cs_args;
    std::map<std::string, std::string> mapArgs;
    std::map<std::string, std::vector<std::string> > mapMultiArgs;
public:
    void ParseParameters(int argc, const char*const argv[]);
    void ReadConfigFile(const std::string& confPath);
    std::vector<std::string> GetArgs(const std::string& strArg);
    /**
     * Return true if the given argument has been manually set
     *
     * @param strArg Argument to get (e.g. "-foo")
     * @return true if the argument has been set
     */
    bool IsArgSet(const std::string& strArg);
    
    /**
     * Return string argument or default value
     *
     * @param strArg Argument to get (e.g. "-foo")
     * @param default (e.g. "1")
     * @return command-line argument or default value
     */
    std::string GetArg(const std::string& strArg, const std::string& strDefault);
    
    /**
     * Return integer argument or default value
     *
     * @param strArg Argument to get (e.g. "-foo")
     * @param default (e.g. 1)
     * @return command-line argument (0 if invalid number) or default value
     */
    int64_t GetArg(const std::string& strArg, int64_t nDefault);
    
    /**
     * Return boolean argument or default value
     *
     * @param strArg Argument to get (e.g. "-foo")
     * @param default (true or false)
     * @return command-line argument or default value
     */
    bool GetBoolArg(const std::string& strArg, bool fDefault);
    
    /**
     * Set an argument if it doesn't already have a value
     *
     * @param strArg Argument to set (e.g. "-foo")
     * @param strValue Value (e.g. "1")
     * @return true if argument gets set, false if it already had a value
     */
    bool SoftSetArg(const std::string& strArg, const std::string& strValue);
    
    /**
     * Set a boolean argument if it doesn't already have a value
     *
     * @param strArg Argument to set (e.g. "-foo")
     * @param fValue Value (e.g. false)
     * @return true if argument gets set, false if it already had a value
     */
    bool SoftSetBoolArg(const std::string& strArg, bool fValue);
    
    // Forces an arg setting. Called by SoftSetArg() if the arg hasn't already
    // been set. Also called directly in testing.
    void ForceSetArg(const std::string& strArg, const std::string& strValue);
};

extern ArgsManager gArgs;

// wrappers using the global ArgsManager:
static inline void ParseParameters(int argc, const char*const argv[])
{
    gArgs.ParseParameters(argc, argv);
}

static inline void ReadConfigFile(const std::string& confPath)
{
    gArgs.ReadConfigFile(confPath);
}

static inline bool SoftSetArg(const std::string& strArg, const std::string& strValue)
{
    return gArgs.SoftSetArg(strArg, strValue);
}

static inline void ForceSetArg(const std::string& strArg, const std::string& strValue)
{
    gArgs.ForceSetArg(strArg, strValue);
}

static inline bool IsArgSet(const std::string& strArg)
{
    return gArgs.IsArgSet(strArg);
}

static inline std::string GetArg(const std::string& strArg, const std::string& strDefault)
{
    return gArgs.GetArg(strArg, strDefault);
}

static inline int64_t GetArg(const std::string& strArg, int64_t nDefault)
{
    return gArgs.GetArg(strArg, nDefault);
}

static inline bool GetBoolArg(const std::string& strArg, bool fDefault)
{
    return gArgs.GetBoolArg(strArg, fDefault);
}

static inline bool SoftSetBoolArg(const std::string& strArg, bool fValue)
{
    return gArgs.SoftSetBoolArg(strArg, fValue);
}




void RenameThread(const char* name);
