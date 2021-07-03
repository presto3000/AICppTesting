// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"

void UHealthBar::NativeConstruct()
{
    //WE can add here
    // Call the Blueprint "Event Construct" node
}

void UHealthBar::set_bar_value_percent(float const value)
{
    if(health_value)
    {
    health_value->SetPercent(value);
    }
}
