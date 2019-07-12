# Ombre
Copyright (c) 2019, The Ombre Project

Copyright (c) 2018, Ryo Currency Project

Copyright (c) 2017, Sumokoin.org

Copyright (c) 2014-2017, The Monero Project

Copyright (c) 2012-2013, The Cryptonote developers
## Development Resources

- Web: [www.ombre.network](http://www.ombre.network)
- GitHub: [https://github.com/ombre-project/ombre](https://github.com/ombre-project/ombre)

## Introduction

Ombre is a cryptonote currency and an indirect for of the well-known Monero currency. Inherited from Monero are strong security, privacy and untraceability features that form a solid basis for further development. Our mission is to enhance the cryptonote protocol to provide a **lightweight**, **secure**, **well maintained** and **actively developed** (no-nonsense) coin.

Some main differences compared to other cryptonote coins are:

 - We use a 60 second block window which reduce transaction times
 - We enforce a minimum transaction mixin of 10 to fight blockchain analysis which could compromise privacy
 - We actively cooperate with other cryptonote coins and do not treat them as competition.


## Development funding

We do not have a premine. Instead we have a project development reward that causes coins to unlock with every block that is found. The algorithm (see below) will start with unlocking 6% of the block reward but gradually reduces to 0% in the next 10 years.  In total a maximum of 2% of the total coin supply will be unlocked for development.

```
f(x) = 0.06 * (1 - sqrt(x)) where x = current_supply / max_supply S.T. current_supply <= max_supply
```

The development fee will be used to pay for development, exchanges and marketing.

## Coin Supply & Emission

- **Total supply**: **1,000,000,000** coins in first 20 years which is followed by a tail emission each year for inflation.
- **Coin symbol**: **OMB**
- **Coin Units**:
  + 1 Nano-Ombre &nbsp;= 0.000000001 **OMB** (10<sup>-9</sup> - _the smallest coin unit_)
  + 1 Micro-Ombre = 0.000001 **OMB** (10<sup>-6</sup>)
  + 1 Milli-Ombre = 0.001 **OMB** (10<sup>-3</sup>)
- **Hash algorithm**: CryptoNight (Proof-Of-Work)
- **Emission scheme**: Ombre's block reward changes _every 6-months_ as the following "Camel" distribution* (inspired by _real-world mining production_ like of crude oil, coal etc. that is often slow at first,
accelerated in the next few years before declined and depleted). This great emission scheme was first introduced in Sumokoin.

## Roadmap 2019

### Q2: Android wallet
We will release an Android wallet which will use remote wallet nodes to scan the blockchain for transactions.

One problem with existing Android wallets for cryptonote coins is that they use close to 1GB of data (Sumokoin) to scan the blockchain. we will solve this by allowing the Android wallet to send the wallet's viewkey to the remote wallet node. With this approach the transaction scanning can be done server side and this will significantly increase the performance of the wallet.

All wallet connections will be SSL encrypted and official wallet nodes will be provided.

### Q2. Blockchain protocol optimisations
The blockchain network communication is not optimized and, for example, doesn't even use compression on large data exchanges. We will add compression and will look into modernizing the RPC protocols.

### Q3. Security audit
We plan on doing a full security audit of the codebase and will setup fuzzing for all exposed network logic. Additionally security enhancements are planned for the ombred daemon, the GUI wallet and the communication channel between both.

### Q3. Web wallet (under consideration)
For this roadmap item we would like to have community feedback first: we think a web wallet would be very convenient for our users but we'll be on the lookout for feedback before starting the implementation.

### Q3. Global pool balancer ((under consideration)
We will implement a lightweight and yet protocol aware loadbalancer to spread the mining load on our network across pools evenly. We will create an incentive for pool owners and miners to join the loadbalancer. A healthy spread of the mining across multiple pools is highly beneficial for the stability of the coin.


## About this Project

This is the core implementation of Ombre. It is open source and completely free to use without restrictions, except for those specified in the license agreement below. There are no restrictions on anyone creating an alternative implementation of Ombre that uses the protocol and network in a compatible manner.

As with many development projects, the repository on Github is considered to be the "staging" area for the latest changes. Before changes are merged into that branch on the main repository, they are tested by individual developers in their own branches, submitted as a pull request, and then subsequently tested by contributors who focus on testing and code reviews. That having been said, the repository should be carefully considered before using it in a production environment, unless there is a patch in the repository for a particular show-stopping issue you are experiencing. It is generally a better idea to use a tagged release for stability.

**Anyone is welcome to contribute to Ombre's codebase!** If you have a fix or code change, feel free to submit is as a pull request directly to the "master" branch. In cases where the change is relatively small or does not affect other parts of the codebase it may be merged in immediately by any one of the collaborators. On the other hand, if the change is particularly large or complex, it is expected that it will be discussed at length either well in advance of the pull request being submitted, or even directly on the pull request.

## License

Please view [LICENSE](LICENSE)

[![License](https://img.shields.io/badge/license-BSD3-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
