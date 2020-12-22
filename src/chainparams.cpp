// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2018 The ZCOREcoin developers
// Copyright (c) 2019-2020 The DNGRcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"
#include <stdio.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);

    //printf("genesis.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
    //printf("genesis.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());

    return genesis;
}


static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "NY Times 09 dec 2019. A (Grudging) Defense 120,000 Banana";
    const CScript genesisOutputScript = CScript() << ParseHex("048d74918012e359970fee87752e2f34416958a6281b93d50819b2a5765c10fe3121fd60712e762fda15c82b31e1cf0912c6bf253756787042d3a97cd6ca88e4ad") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 394200; // one year
        consensus.nMasternodePaymentsStartBlock = 4000; // 4 days
        consensus.nMasternodePaymentsIncreaseBlock = 158000; // not used
        consensus.nMasternodePaymentsIncreasePeriod = 576*30; // not used
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 22180; // year 10000+
        consensus.nBudgetPaymentsCycleBlocks = 20160;//21 days;
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockStartBlock = 2100000000; // year 10000+
        consensus.nSuperblockCycle = 20160;//21 days
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 0; // FIX
        consensus.BIP34Hash = uint256S("0x00000a237b793f047e553def81077e61d79655fdaf51888d0fb9ca65d84061b2"); // FIX
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan =  40 * 1.5 * 60; // DNGRcoin: 1 hour, 40 blocks  // used only for KGW and Bitcoin Diff
        consensus.nPowTargetSpacing =  1.5 * 60;      // DNGRcoin: 90 seconds // soft change to nPowAgo2018TargetSpacing after mPowDGWReconfigureAgo2018Height
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nPowDGWHeight = 0;
	consensus.nPowDGW3Height = 0;  //New retarget
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1502280000; // Aug 9th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1533816000; // Aug 9th, 2018

        // Consensus Update Ago 2018
        consensus.mPowDGWReconfigureAgo2018Height = 0;
        consensus.nPowAgo2018TargetSpacing = 1.5 * 60;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x1b;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0x2b;
        vAlertPubKey = ParseHex("048d74918012e359970fee87752e2f34416958a6281b93d50819b2a5765c10fe3121fd60712e762fda15c82b31e1cf0912c6bf253756787042d3a97cd6ca88e4ad");
        nDefaultPort = 49002;
        nMaxTipAge = 6 * 60 * 60; // ~270 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1575892800, 2148678, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //printf("block.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
        assert(consensus.hashGenesisBlock == uint256S("0x00000a237b793f047e553def81077e61d79655fdaf51888d0fb9ca65d84061b2"));
        assert(genesis.hashMerkleRoot     == uint256S("0x7123ced7a772e8380a5145cde9511454a2a1fea29ff652b77561d92e1e8683d2"));

        vSeeds.push_back(CDNSSeedData("207.244.105.200", "207.244.105.200"));
        vSeeds.push_back(CDNSSeedData("91.210.169.170", "91.210.169.170"));
        vSeeds.push_back(CDNSSeedData("212.237.1.56", "212.237.1.56"));
        vSeeds.push_back(CDNSSeedData("96.30.194.160", "96.30.194.160"));
        vSeeds.push_back(CDNSSeedData("95.111.251.34", "95.111.251.34"));
        vSeeds.push_back(CDNSSeedData("92.38.163.183", "92.38.163.183"));
        vSeeds.push_back(CDNSSeedData("91.200.226.208", "91.200.226.208"));
        vSeeds.push_back(CDNSSeedData("118.24.236.176", "118.24.236.176"));
        vSeeds.push_back(CDNSSeedData("139.99.237.233", "139.99.237.233"));
        vSeeds.push_back(CDNSSeedData("37.187.152.220", "37.187.152.220"));
        vSeeds.push_back(CDNSSeedData("45.55.61.36", "45.55.61.36"));
        vSeeds.push_back(CDNSSeedData("91.210.168.242", "91.210.168.242"));
        vSeeds.push_back(CDNSSeedData("144.91.99.72", "144.91.99.72"));
        vSeeds.push_back(CDNSSeedData("122.148.149.97", "122.148.149.97"));
        vSeeds.push_back(CDNSSeedData("199.247.25.1", "199.247.25.1"));
	vSeeds.push_back(CDNSSeedData("3.128.107.229", "3.128.107.229"));

        //vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        //vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        // DNGRcoin addresses start with 'd'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,90);
        // DNGRcoin script addresses start with '1'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,0);
        // DNGRcoin private keys start with '3' or 'C' 
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,80);
        // DNGRcoin BIP32 pubkeys start with '2p5V' ('xpub' (Bitcoin defaults))
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x08)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // DNGRcoin BIP32 prvkeys start with '32Pa' ('xprv' (Bitcoin defaults))
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x09)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // DNGRcoin BIP44 coin type is '5'
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x81)(0x00)(0x00)(0x05).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        strSporkPubKey = "048d74918012e359970fee87752e2f34416958a6281b93d50819b2a5765c10fe3121fd60712e762fda15c82b31e1cf0912c6bf253756787042d3a97cd6ca88e4ad";
        strMasternodePaymentsPubKey = "048d74918012e359970fee87752e2f34416958a6281b93d50819b2a5765c10fe3121fd60712e762fda15c82b31e1cf0912c6bf253756787042d3a97cd6ca88e4ad";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (      0, uint256S("0x00000a237b793f047e553def81077e61d79655fdaf51888d0fb9ca65d84061b2")) // 09 dec 2019 @ 12:00pm (UTC)
            (   6666, uint256S("0x00000000d13b24d4dc2dcfd4d4e7fae58d2f7299f9ea335a44bb82991691e951")) // 17-Dec-19 10:58:06  (UTC)
	    (  37022, uint256S("0x0000000024ff4bca5af3cf715371f041ae5dfb9ab24b96d8945fdf65dea3ac2e")) // 19th Jan 2020 19:37:40 (UTC)
	    (  42780, uint256S("0x0000000014774dc3525e267f112edaa9a84568a247c1c1ceedcf108a15948cd8")) // 26th Jan 2020 06:09:06 (UTC)
            (  70123, uint256S("0x00000000b04491bcba9d2877332859401e51e7a0a852dfce489d017277971b4b")) // 25th Feb 2020 06:57:15 (UTC)
            ( 329500, uint256S("0x00000002d4b13e8c7129d9254a2dd533d414165a622b8b3639a545a7cf865d81")),// 17th Dec 2020 07:18:25 (UTC)
            1608189505, // * UNIX timestamp of last checkpoint block
            73731,      // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            4800        // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 262800;
        consensus.nMasternodePaymentsStartBlock = 750; // not true, but it's ok as long as it's less then nMasternodePaymentsIncreaseBlock
        consensus.nMasternodePaymentsIncreaseBlock = 46000;
        consensus.nMasternodePaymentsIncreasePeriod = 576;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 2100000000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 2100000000; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockCycle = 24; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 0; // FIX
        consensus.BIP34Hash = uint256S("0x0000025674bfc679d36886f9f3b73d501a57d84a400e8579140a182a0e914134"); // FIX
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 60 * 60; // DNGRcoin: 1 hour  // used only for KGW and Bitcoin Diff
        consensus.nPowTargetSpacing = 2 * 60;   // DNGRcoin: 1 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
	consensus.nPowDGWHeight = 512;
	consensus.nPowDGW3Height = 550;  //New retarget
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1502280000; // Aug 9th, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1533816000; // Aug 9th, 2018

        // Consensus Update Ago 2018
        consensus.mPowDGWReconfigureAgo2018Height = 550;
        consensus.nPowAgo2018TargetSpacing = 2 * 60;

        pchMessageStart[0] = 0x12;
        pchMessageStart[1] = 0x41;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0x3b;
        vAlertPubKey = ParseHex("048d74918012e359970fee87752e2f34416958a6281b93d50819b2a5765c10fe3121fd60712e762fda15c82b31e1cf0912c6bf253756787042d3a97cd6ca88e4ad");

        nDefaultPort = 49012;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1575892860, 442222, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //printf("block.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
        assert(consensus.hashGenesisBlock == uint256S("0x0000025674bfc679d36886f9f3b73d501a57d84a400e8579140a182a0e914134"));
        assert(genesis.hashMerkleRoot     == uint256S("0x7123ced7a772e8380a5145cde9511454a2a1fea29ff652b77561d92e1e8683d2"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("dngrcoin.me",  "testnet.dngrcoin.cash"));

        // Testnet DNGRcoin addresses start with 'n'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,112);
        // Testnet DNGRcoin script addresses start with '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,20);
        // Testnet private keys start with '9' or 'c' (Bitcoin defaults) (?)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
        // Testnet DNGRcoin BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x03)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet DNGRcoin BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x08)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet DNGRcoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x89)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "048d74918012e359970fee87752e2f34416958a6281b93d50819b2a5765c10fe3121fd60712e762fda15c82b31e1cf0912c6bf253756787042d3a97cd6ca88e4ad";
        strMasternodePaymentsPubKey = "048d74918012e359970fee87752e2f34416958a6281b93d50819b2a5765c10fe3121fd60712e762fda15c82b31e1cf0912c6bf253756787042d3a97cd6ca88e4ad";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, uint256S("0x0000025674bfc679d36886f9f3b73d501a57d84a400e8579140a182a0e914134")), // 09 dec 2019 @ 12:01pm (UTC)
            	1575892860, // * UNIX timestamp of last checkpoint block 
            	1,       // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            	500        // * estimated number of transactions per day after checkpoint
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMasternodePaymentsStartBlock = 240;
        consensus.nMasternodePaymentsIncreaseBlock = 350;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 1000;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 1500;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 0; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 60 * 60; // DNGRcoin: 1 hour // used only for KGW and Bitcoin Diff
        consensus.nPowTargetSpacing = 2 * 60; // DNGRcoin: 2 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
	consensus.nPowDGWHeight = 100;
	consensus.nPowDGW3Height = 200;  //New retarget
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;

        // Consensus Update Apr 2018
        consensus.mPowDGWReconfigureAgo2018Height = 1;
        consensus.nPowAgo2018TargetSpacing = 2 * 60;

        pchMessageStart[0] = 0x13;
        pchMessageStart[1] = 0x11;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0x46;
        nMaxTipAge = 12 * 60 * 60;
        nDefaultPort = 49022;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1575892920, 113089, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //printf("block.GetHash() == %s\n", genesis.GetHash().ToString().c_str());
        assert(consensus.hashGenesisBlock == uint256S("0x00000b9716a40e1a15b8de87609272315b70d293a76844c8a3428d2a9ffedd26"));
        assert(genesis.hashMerkleRoot     == uint256S("0x7123ced7a772e8380a5145cde9511454a2a1fea29ff652b77561d92e1e8683d2"));


        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x00000b9716a40e1a15b8de87609272315b70d293a76844c8a3428d2a9ffedd26")), // 09 dec 2019 @ 12:02pm (UTC)
            //0,
            //0,
            //0
            1575892920, // * UNIX timestamp of last checkpoint block
        };
        // Regtest DNGRcoin addresses start with 'n'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,112);
        // Regtest DNGRcoin script addresses start with '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,20);
        // Regtest private keys start with '9' or 'c' (Bitcoin defaults) (?)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
        // Regtest DNGRcoin BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x05)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest DNGRcoin BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x07)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Regtest DNGRcoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x89)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();
   }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
