#include <Geode/Geode.hpp>
#include "YouTubeAPI.hpp"
#include <matjson.hpp>

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());

		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
			this,
			menu_selector(MyMenuLayer::onMyButton)
		);

		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		myButton->setID("my-button"_spr);

		menu->updateLayout();

		return true;
	}

	void onMyButton(CCObject*) {
		YoutubeAPI::get()->setApiKey("AIzaSyC1XDn6xWLAuaYGTvPPueJ4IhjZRxWhMmM");
		matjson::Value testing = YoutubeAPI::get()->getSearchResults("arcticwoof", "");
		FLAlertLayer::create("!!! EXTREMELY IMPORTANT MESSAGE !!!", "h", "OK")->show();
	}
};