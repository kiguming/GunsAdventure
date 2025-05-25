// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UI/ArguShopWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Player/Save/BaseSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Player/UI/ArgumentBaseWidget.h"
#include "Components/VerticalBox.h"
#include "Components/CanvasPanel.h"

void UArguShopWidget::NativeConstruct()
{
	if (PrevButton) {
		PrevButton->OnClicked.AddDynamic(this, &UArguShopWidget::ClickPrev);
	}
	if (NextButton) {
		NextButton->OnClicked.AddDynamic(this, &UArguShopWidget::ClickNext);
	}
	if (ArgumentButton1) {
		ArgumentButton1->OnClicked.AddDynamic(this, &UArguShopWidget::ClickedArgu1);
	}
	if (ArgumentButton2) {
		ArgumentButton2->OnClicked.AddDynamic(this, &UArguShopWidget::ClickedArgu2);
	}
	if (ArgumentButton3) {
		ArgumentButton3->OnClicked.AddDynamic(this, &UArguShopWidget::ClickedArgu3);
	}
	if (ArgumentButton4) {
		ArgumentButton4->OnClicked.AddDynamic(this, &UArguShopWidget::ClickedArgu4);
	}


	LoadInstance = Cast<UBaseSaveGame>(UGameplayStatics::CreateSaveGameObject(UBaseSaveGame::StaticClass()));
	if (LoadInstance) {
		LoadInstance->SaveSlotName = "MyGames";
		LoadInstance->UserIndex = 0;
		LoadInstance = Cast<UBaseSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadInstance->SaveSlotName, LoadInstance->UserIndex));
	}

	
	if (LoadInstance) {
		if (MoneysText) {
			MoneysText->SetText(FText::FromString(FString::Printf(TEXT("%dG"), LoadInstance->Money)));
		}
		
		if (LoadInstance->BuyList.Num() != ShopArgument_Lists.Num()) { //만약 버전차이로 갯수가 다르다면
			UE_LOG(LogTemp, Log, TEXT("이거 호출됨")); //3
			int32 CountToAdd = ShopArgument_Lists.Num() - LoadInstance->BuyList.Num(); //차이만큼 계산해서
			int32 InstanceCount = LoadInstance->BuyList.Num();
			for (int32 i = 0; i < CountToAdd; i++) {
				LoadInstance->BuyList.Add(false);
			}
		}




		UE_LOG(LogTemp, Log, TEXT("상점안의 배열 갯수 : %d"), ShopArgument_Lists.Num()); //3
		UE_LOG(LogTemp, Log, TEXT("로드 파일 안의 배열 갯수 : %d"), LoadInstance->BuyList.Num()); //0

		ArguCounter = 0; //증강페이지를 1첫페이지로 만듬.
		ShowArgument();
	}
}

void UArguShopWidget::ClickNext()
{
	if (ShopArgument_Lists.IsValidIndex(ArguCounter + 4)) {
		ArguCounter += 4;
		ShowArgument();
	}
}

void UArguShopWidget::ClickPrev()
{
	if (ShopArgument_Lists.IsValidIndex(ArguCounter-4)) {
		ArguCounter -= 4;
		ShowArgument();
	}
}

void UArguShopWidget::ClickedArgu1()
{
	if (LoadInstance) {
		if (BuyCard1->GetPrice() <= LoadInstance->Money) {
			YesNoBox->SetVisibility(ESlateVisibility::Visible);
			if (YesButton) {
				YesButton->OnClicked.Clear();
				YesButton->OnClicked.AddDynamic(this, &UArguShopWidget::ClickedBuyArgu1);
			}
			if (NoButton) {
				NoButton->OnClicked.Clear();
				NoButton->OnClicked.AddDynamic(this, &UArguShopWidget::CancleClicked);
			}

		}
	}
	
}

void UArguShopWidget::ClickedArgu2()
{
	if (LoadInstance) {
		if (BuyCard2->GetPrice() <= LoadInstance->Money) {
			YesNoBox->SetVisibility(ESlateVisibility::Visible);
			if (YesButton) {
				YesButton->OnClicked.Clear();
				YesButton->OnClicked.AddDynamic(this, &UArguShopWidget::ClickedBuyArgu2);
			}
			if (NoButton) {
				NoButton->OnClicked.Clear();
				NoButton->OnClicked.AddDynamic(this, &UArguShopWidget::CancleClicked);
			}

		}
	}
}

void UArguShopWidget::ClickedArgu3()
{
	if (LoadInstance) {
		if (BuyCard3->GetPrice() <= LoadInstance->Money) {
			YesNoBox->SetVisibility(ESlateVisibility::Visible);
			if (YesButton) {
				YesButton->OnClicked.Clear();
				YesButton->OnClicked.AddDynamic(this, &UArguShopWidget::ClickedBuyArgu3);
			}
			if (NoButton) {
				NoButton->OnClicked.Clear();
				NoButton->OnClicked.AddDynamic(this, &UArguShopWidget::CancleClicked);
			}

			
		}
	}
}

void UArguShopWidget::ClickedArgu4()
{
	if (LoadInstance) {
		if (BuyCard4->GetPrice() <= LoadInstance->Money) {
			YesNoBox->SetVisibility(ESlateVisibility::Visible);
			if (YesButton) {
				YesButton->OnClicked.Clear();
				YesButton->OnClicked.AddDynamic(this, &UArguShopWidget::ClickedBuyArgu4);
			}
			if (NoButton) {
				NoButton->OnClicked.Clear();
				NoButton->OnClicked.AddDynamic(this, &UArguShopWidget::CancleClicked);
			}

			
		}
	}
}

void UArguShopWidget::ClickedBuyArgu1()
{
	YesNoBox->SetVisibility(ESlateVisibility::Hidden);
	if (LoadInstance) {//LoadInstance확인하고
		LoadInstance->BuyList[ArguCounter] = true;

		LoadInstance->SaveSlotName = "MyGames";
		LoadInstance->UserIndex = 0;
		LoadInstance->Money -= BuyCard1->GetPrice();
		UGameplayStatics::SaveGameToSlot(LoadInstance, LoadInstance->SaveSlotName, LoadInstance->UserIndex);
	}
	ShowArgument();
}

void UArguShopWidget::ClickedBuyArgu2()
{
	YesNoBox->SetVisibility(ESlateVisibility::Hidden);
	if (LoadInstance) {//LoadInstance확인하고
		LoadInstance->BuyList[ArguCounter+1] = true;

		LoadInstance->SaveSlotName = "MyGames";
		LoadInstance->UserIndex = 0;
		LoadInstance->Money -= BuyCard2->GetPrice();
		UGameplayStatics::SaveGameToSlot(LoadInstance, LoadInstance->SaveSlotName, LoadInstance->UserIndex);
	}
	ShowArgument();
}

void UArguShopWidget::ClickedBuyArgu3()
{
	YesNoBox->SetVisibility(ESlateVisibility::Hidden);
	if (LoadInstance) {//LoadInstance확인하고
		LoadInstance->BuyList[ArguCounter+2] = true;

		LoadInstance->SaveSlotName = "MyGames";
		LoadInstance->UserIndex = 0;
		LoadInstance->Money -= BuyCard3->GetPrice();
		UGameplayStatics::SaveGameToSlot(LoadInstance, LoadInstance->SaveSlotName, LoadInstance->UserIndex);
	}
	ShowArgument();
}

void UArguShopWidget::ClickedBuyArgu4()
{
	YesNoBox->SetVisibility(ESlateVisibility::Hidden);
	if (LoadInstance) {//LoadInstance확인하고
		LoadInstance->BuyList[ArguCounter+3] = true;

		LoadInstance->SaveSlotName = "MyGames";
		LoadInstance->UserIndex = 0;
		LoadInstance->Money -= BuyCard4->GetPrice();
		UGameplayStatics::SaveGameToSlot(LoadInstance, LoadInstance->SaveSlotName, LoadInstance->UserIndex);
	}
	ShowArgument();
}

void UArguShopWidget::ShowArgument()
{
	ClearArgument();
	if (ShopArgument_Lists.IsValidIndex(ArguCounter)) {
		BuyCard1 = CreateWidget<UArgumentBaseWidget>(GetWorld(), ShopArgument_Lists[ArguCounter]);
		VerticalBox1->AddChild(BuyCard1);
		ArgumentPrice1->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyCard1->GetPrice())));
		VerticalBox1->AddChild(ArgumentPrice1);
		VerticalBox1->AddChild(ArgumentButton1);
		if (!LoadInstance->BuyList[ArguCounter]) {//만약 팔리지않았다면
			ArgumentPrice1->SetVisibility(ESlateVisibility::Visible);
			ArgumentButton1->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			VerticalBox1->AddChild(isBuy1);
			ArgumentPrice1->SetVisibility(ESlateVisibility::Hidden);//팔렸다면 구매버튼이랑 가격을 띄울필요가없음.
			ArgumentButton1->SetVisibility(ESlateVisibility::Hidden);
			isBuy1->SetVisibility(ESlateVisibility::Visible);
		}
	}
	if (ShopArgument_Lists.IsValidIndex(ArguCounter+1)) {
		BuyCard2 = CreateWidget<UArgumentBaseWidget>(GetWorld(), ShopArgument_Lists[ArguCounter+1]);
		VerticalBox2->AddChild(BuyCard2);
		ArgumentPrice2->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyCard2->GetPrice())));
		VerticalBox2->AddChild(ArgumentPrice2);
		VerticalBox2->AddChild(ArgumentButton2);
		if (!LoadInstance->BuyList[ArguCounter+1]) {//만약 팔리지않았다면
			ArgumentPrice2->SetVisibility(ESlateVisibility::Visible);
			ArgumentButton2->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			VerticalBox2->AddChild(isBuy2);
			ArgumentPrice2->SetVisibility(ESlateVisibility::Hidden);//팔렸다면 구매버튼이랑 가격을 띄울필요가없음.
			ArgumentButton2->SetVisibility(ESlateVisibility::Hidden);
			isBuy2->SetVisibility(ESlateVisibility::Visible);
		}
	}
	if (ShopArgument_Lists.IsValidIndex(ArguCounter+2)) {
		BuyCard3 = CreateWidget<UArgumentBaseWidget>(GetWorld(), ShopArgument_Lists[ArguCounter + 2]);
		VerticalBox3->AddChild(BuyCard3);
		ArgumentPrice3->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyCard3->GetPrice())));
		VerticalBox3->AddChild(ArgumentPrice3);
		VerticalBox3->AddChild(ArgumentButton3);	
		if (!LoadInstance->BuyList[ArguCounter+2]) {//만약 팔리지않았다면
			ArgumentPrice3->SetVisibility(ESlateVisibility::Visible);
			ArgumentButton3->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			VerticalBox3->AddChild(isBuy3);
			ArgumentPrice3->SetVisibility(ESlateVisibility::Hidden);//팔렸다면 구매버튼이랑 가격을 띄울필요가없음.
			ArgumentButton3->SetVisibility(ESlateVisibility::Hidden);
			isBuy3->SetVisibility(ESlateVisibility::Visible);
		}
	}
	if (ShopArgument_Lists.IsValidIndex(ArguCounter+3)) {
		BuyCard4 = CreateWidget<UArgumentBaseWidget>(GetWorld(), ShopArgument_Lists[ArguCounter + 3]);
		VerticalBox4->AddChild(BuyCard4);
		ArgumentPrice4->SetText(FText::FromString(FString::Printf(TEXT("%dG"), BuyCard4->GetPrice())));
		VerticalBox4->AddChild(ArgumentPrice4);
		VerticalBox4->AddChild(ArgumentButton4);
		if (!LoadInstance->BuyList[ArguCounter + 3]) {//만약 팔리지않았다면
			ArgumentPrice4->SetVisibility(ESlateVisibility::Visible);
			ArgumentButton4->SetVisibility(ESlateVisibility::Visible);
		}
		else {
			VerticalBox4->AddChild(isBuy4);
			ArgumentPrice4->SetVisibility(ESlateVisibility::Hidden);//팔렸다면 구매버튼이랑 가격을 띄울필요가없음.
			ArgumentButton4->SetVisibility(ESlateVisibility::Hidden);
			isBuy4->SetVisibility(ESlateVisibility::Visible);
		}
	}
	if (MoneysText) {
		MoneysText->SetText(FText::FromString(FString::Printf(TEXT("%dG"), LoadInstance->Money)));
	}
}

void UArguShopWidget::ClearArgument()
{
	VerticalBox1->RemoveChild(BuyCard1);
	VerticalBox1->RemoveChild(ArgumentPrice1);
	VerticalBox1->RemoveChild(ArgumentButton1);
	VerticalBox1->RemoveChild(isBuy1);

	VerticalBox2->RemoveChild(BuyCard2);
	VerticalBox2->RemoveChild(ArgumentPrice2);
	VerticalBox2->RemoveChild(ArgumentButton2);
	VerticalBox2->RemoveChild(isBuy2);

	VerticalBox3->RemoveChild(BuyCard3);
	VerticalBox3->RemoveChild(ArgumentPrice3);
	VerticalBox3->RemoveChild(ArgumentButton3);
	VerticalBox3->RemoveChild(isBuy3);

	VerticalBox4->RemoveChild(BuyCard4);
	VerticalBox4->RemoveChild(ArgumentPrice4);
	VerticalBox4->RemoveChild(ArgumentButton4);
	VerticalBox4->RemoveChild(isBuy4);

	
}

void UArguShopWidget::CancleClicked()
{
	if (YesNoBox) {
		YesNoBox->SetVisibility(ESlateVisibility::Hidden);//확인창을 안보이게바꿈
	}
	
}


