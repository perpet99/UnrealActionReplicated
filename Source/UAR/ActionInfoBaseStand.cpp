// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionInfoBaseStand.h"
#include "UARCharacter.h"

//void UActionInfoBaseAttack::PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker)
//{
//	/*Super::PreReplication(ChangedPropertyTracker);
//	DOREPLIFETIME_ACTIVE_OVERRIDE(UActionInfoBaseAttack, Name, GetActionID() == player->CurAction>->GetActionID());*/
//}
void UActionInfoBaseAttack::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(UActionInfoBaseAttack, Name, COND_Custom);
	//DOREPLIFETIME(UActionInfoBaseAttack, Name);
}
bool UActionInfoBaseAttack::IsSupportedForNetworking() const
{
	return true;
}
