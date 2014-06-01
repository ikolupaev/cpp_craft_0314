#ifndef _MULTICAST_COMMUNICATION_CQS_STRUCTURES_H_
#define _MULTICAST_COMMUNICATION_CQS_STRUCTURES_H_


namespace multicast_communication
{
	struct short_quote_message
	{
		char SecuritySymbol[3];
		char QuoteCondition;
		char LULDIndicator;
		char Reserved1;
		char BidPriceDenominatorIndicator;
		char BidShortPrice[8];
		char BidSizeUnitsofTrade[3];
		char Reserved2;
		char OfferPriceDenominatorIndicator;
		char OfferShortPrice[8];
		char OfferSizeinUnitsofTrade[3];
		char Reserved3;
		char NationalBBOIndicator;
		char FINRABBOIndicator;
	};

	struct long_quote_message
	{
		char SecuritySymbol[11];
		char TemporarySuffix;
		char TestMessageIndicator;
		char PrimaryListingMarketParticipantIdentifier;
		char SIPGeneratedMessageIdentifier;
		char Reserved1;
		char FinancialStatus;
		char CurrencyIndicator[3];
		char InstrumentType[1];
		char CancelCorrectionIndicator;
		char SettlementCondition;
		char MarketCondition;
		char QuoteCondition;
		char LULDIndicator;
		char RetailInterestIndicator;
		char BidPriceBandDenominatorIndicator;
		char BidPrice[12];
		char BidSizeinUnitsofTrade[7];
		char OfferPriceBandDenominatorIndicator;
		char OfferPrice[12];
		char OfferSizeinUnitsofTrade[7];
		char FINRAMarketMakerID[4];
		char Reserved2;
		char NationalBBOLULDIndicator;
		char FINRABBOLULDIndicator;
		char ShortSaleRestrictionIndicator;
		char Reserved3;
		char NationalBBOIndicator;
		char FINRABBOIndicator;
	};
}

#endif