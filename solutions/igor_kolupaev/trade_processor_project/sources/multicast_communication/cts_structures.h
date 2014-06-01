#ifndef _MULTICAST_COMMUNICATION_CTS_STRUCTURES_H_
#define _MULTICAST_COMMUNICATION_CTS_STRUCTURES_H_


namespace multicast_communication
{
	struct short_trade_message
	{
		char SecuritySymbol[3];
		char SaleCondition;
		char TradeVolume[4];
		char PriceDenominator;
		char TradePrice[8];
		char ConsolidatedIndicator;
		char ParticipantIndicator;
		char Reserved;
	};

	struct long_trade_message
	{
		char SecuritySymbol[11];
		char TemporarySuffix;
		char TestMessageIndicator;
		char TradeReportingFacilityIdentifier;
		char PrimaryListingMarketParticipantIdentifier;
		char Reserved1;
		char FinancialStatus;
		char CurrencyIndicator[3];
		char HeldTradeIndicator;
		char InstrumentType;
		char SellerSaleDays[3];
		char SaleCondition[4];
		char TradeThroughExemptIndicator;
		char ShortSaleRestrictionIndicator;
		char Reserved2;
		char PriceDenominatorIndicator;
		char TradePrice[12];
		char TradeVolume[9];
		char ConsolidatedIndicator;
		char ParticipantIndicator;
		char Reserved3;
		char StopStockIndicator;
	};
}

#endif