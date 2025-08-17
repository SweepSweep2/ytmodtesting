#include "YoutubeAPI.hpp"
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <matjson.hpp>

using namespace geode::prelude;

YoutubeAPI * YoutubeAPI::instance = nullptr;

YoutubeAPI* YoutubeAPI::get() {
    if (!instance) {
        instance = new YoutubeAPI();
    }

    return instance;
};

std::string YoutubeAPI::getApiKey() {
    return m_apiKey;
}

std::string YoutubeAPI::getVideoId() {
    return m_videoId;
}

std::string YoutubeAPI::getChannelId() {
    return m_channelId;
}

std::string YoutubeAPI::getSearchQuery() {
    return m_searchQuery;
}

void YoutubeAPI::setApiKey(std::string apiKey) {
    m_apiKey = apiKey;
}

void YoutubeAPI::setVideoId(std::string videoId) {
    m_videoId = videoId;
}

void YoutubeAPI::setChannelId(std::string channelId) {
    m_channelId = channelId;
}

void YoutubeAPI::setSearchQuery(std::string searchQuery) {
    m_searchQuery = searchQuery;
}

matjson::Value YoutubeAPI::getVideoInfo(std::string videoId) {
    m_videoInfo = matjson::Value();

    YoutubeAPI::m_webListener.bind([this, videoId](web::WebTask::Event* e) {
        if (web::WebResponse* res = e->getValue()) { // if the download was successful
            std::string finalResult = res->string().unwrapOr("Failed to get video info!"); // final download

            if (finalResult == "Failed to get video info!") {
                log::error("Failed to get video info for video ID {}!", videoId);
            } else {
                auto result = matjson::parse(finalResult);

                if (result.isErr()) {
                    log::error("Failed to parse video info for video ID {}: {}", videoId, result.unwrapErr());
                } else {
                    m_videoInfo = result.unwrapOr("Failed to parse video info!");
                    
                    if (m_videoInfo == "Failed to parse video info!") {
                        log::error("Failed to parse video info for video ID {}!", videoId);
                        m_videoInfo = matjson::Value();
                    } else {
                        log::info("Successfully retrieved video info for video ID {}!", videoId);
                    }
                }
            }
        }
    });

    web::WebRequest request;
    YoutubeAPI::m_webListener.setFilter(request.get("https://www.googleapis.com/youtube/v3/videos?part=snippet,contentDetails,statistics,player,status,topicDetails,recordingDetails,localizations&id=" + videoId + "&key=" + m_apiKey)); // idk

    return m_videoInfo;
}

matjson::Value YoutubeAPI::getVideoInfo() {
    m_videoInfo = matjson::Value();

    YoutubeAPI::m_webListener.bind([this](web::WebTask::Event* e) {
        if (web::WebResponse* res = e->getValue()) { // if the download was successful
            std::string finalResult = res->string().unwrapOr("Failed to get video info!"); // final download

            if (finalResult == "Failed to get video info!") {
                log::error("Failed to get video info for video ID {}!", m_videoId);
            } else {
                auto result = matjson::parse(finalResult);

                if (result.isErr()) {
                    log::error("Failed to parse video info for video ID {}: {}", m_videoId, result.unwrapErr());
                } else {
                    m_videoInfo = result.unwrapOr("Failed to parse video info!");
                    
                    if (m_videoInfo == "Failed to parse video info!") {
                        log::error("Failed to parse video info for video ID {}!", m_videoId);
                        m_videoInfo = matjson::Value();
                    } else {
                        log::info("Successfully retrieved video info for video ID {}!", m_videoId);
                    }
                }
            }
        }
    });

    web::WebRequest request;
    YoutubeAPI::m_webListener.setFilter(request.get("https://www.googleapis.com/youtube/v3/videos?part=snippet,contentDetails,statistics,player,status,topicDetails,recordingDetails,localizations&id=" + m_videoId + "&key=" + m_apiKey)); // idk

    return m_videoInfo;
}

matjson::Value YoutubeAPI::getSubscriptions(std::string channelId, std::string pageToken) {
    m_channelSubscriptions = matjson::Value();

    YoutubeAPI::m_webListener.bind([this, channelId](web::WebTask::Event* e) {
        if (web::WebResponse* res = e->getValue()) { // if the download was successful
            std::string finalResult = res->string().unwrapOr("Failed to get subscriptions!"); // final download

            if (finalResult == "Failed to get subscriptions!") {
                log::error("Failed to get subscriptions for channel ID {}!", channelId);
            } else {
                auto result = matjson::parse(finalResult);

                if (result.isErr()) {
                    log::error("Failed to parse subscriptions for channel ID {}: {}", channelId, result.unwrapErr());
                } else {
                    m_channelSubscriptions = result.unwrapOr("Failed to parse channel subscriptions!");
                    log::info("Channel subscriptions: {}", m_channelSubscriptions.dump(4));
                    
                    if (m_channelSubscriptions == "Failed to parse channel subscriptions!") {
                        log::error("Failed to parse channel subscriptions for channel ID {}!", channelId);
                        m_channelSubscriptions = matjson::Value();
                    } else {
                        log::info("Successfully retrieved subscriptions for channel ID {}!", channelId);
                        log::info("Subscriptions: {}", m_channelSubscriptions["items"][1]["snippet"]["title"].asString().unwrapOr("No title found"));
                    }
                }
            }
        }
    });

    web::WebRequest request;
    YoutubeAPI::m_webListener.setFilter(request.get("https://www.googleapis.com/youtube/v3/subscriptions?part=contentDetails,id,snippet,subscriberSnippet&channelId=" + channelId + "&key=" + m_apiKey + "&pageToken=" + pageToken)); // idk

    return m_channelSubscriptions;
}

matjson::Value YoutubeAPI::getSubscriptions(std::string channelId) {
    m_channelSubscriptions = matjson::Value();

    YoutubeAPI::m_webListener.bind([this, channelId](web::WebTask::Event* e) {
        if (web::WebResponse* res = e->getValue()) { // if the download was successful
            std::string finalResult = res->string().unwrapOr("Failed to get subscriptions!"); // final download

            if (finalResult == "Failed to get subscriptions!") {
                log::error("Failed to get subscriptions for channel ID {}!", channelId);
            } else {
                auto result = matjson::parse(finalResult);

                if (result.isErr()) {
                    log::error("Failed to parse subscriptions for channel ID {}: {}", channelId, result.unwrapErr());
                } else {
                    m_channelSubscriptions = result.unwrapOr("Failed to parse channel subscriptions!");
                    log::info("Channel subscriptions: {}", m_channelSubscriptions.dump(4));
                    
                    if (m_channelSubscriptions == "Failed to parse channel subscriptions!") {
                        log::error("Failed to parse channel subscriptions for channel ID {}!", channelId);
                        m_channelSubscriptions = matjson::Value();
                    } else {
                        log::info("Successfully retrieved subscriptions for channel ID {}!", channelId);
                        log::info("Subscriptions: {}", m_channelSubscriptions["items"][0]["snippet"]["title"].asString().unwrapOr("No title found"));
                    }
                }
            }
        }
    });

    web::WebRequest request;
    YoutubeAPI::m_webListener.setFilter(request.get("https://www.googleapis.com/youtube/v3/subscriptions?part=contentDetails,id,snippet,subscriberSnippet&channelId=" + channelId + "&key=" + m_apiKey)); // idk

    return m_channelSubscriptions;
}

matjson::Value YoutubeAPI::getSubscriptions() {
    m_channelSubscriptions = matjson::Value();

    YoutubeAPI::m_webListener.bind([this](web::WebTask::Event* e) {
        if (web::WebResponse* res = e->getValue()) { // if the download was successful
            std::string finalResult = res->string().unwrapOr("Failed to get subscriptions!"); // final download

            if (finalResult == "Failed to get subscriptions!") {
                log::error("Failed to get subscriptions for channel ID {}!", m_channelId);
            } else {
                auto result = matjson::parse(finalResult);

                if (result.isErr()) {
                    log::error("Failed to parse subscriptions for channel ID {}: {}", m_channelId, result.unwrapErr());
                } else {
                    m_channelSubscriptions = result.unwrapOr("Failed to parse channel subscriptions!");
                    log::info("Channel subscriptions: {}", m_channelSubscriptions.dump(4));
                    
                    if (m_channelSubscriptions == "Failed to parse channel subscriptions!") {
                        log::error("Failed to parse channel subscriptions for channel ID {}!", m_channelId);
                        m_channelSubscriptions = matjson::Value();
                    } else {
                        log::info("Successfully retrieved subscriptions for channel ID {}!", m_channelId);
                        log::info("Subscriptions: {}", m_channelSubscriptions["items"][0]["snippet"]["title"].asString().unwrapOr("No title found"));
                    }
                }
            }
        }
    });

    web::WebRequest request;
    YoutubeAPI::m_webListener.setFilter(request.get("https://www.googleapis.com/youtube/v3/subscriptions?part=contentDetails,id,snippet,subscriberSnippet&channelId=" + m_channelId + "&key=" + m_apiKey)); // idk

    return m_channelSubscriptions;
}

matjson::Value YoutubeAPI::getSearchResults(std::string query, std::string pageToken) {
    m_searchResults = matjson::Value();

    YoutubeAPI::m_webListener.bind([this, query, pageToken](web::WebTask::Event* e) {
        if (web::WebResponse* res = e->getValue()) { // if the download was successful
            std::string finalResult = res->string().unwrapOr("Failed to get search results!"); // final download

            if (finalResult == "Failed to get search results!") {
                log::error("Failed to get search results for query {}!", query);
            } else {
                auto result = matjson::parse(finalResult);

                if (result.isErr()) {
                    log::error("Failed to parse search results for query {}: {}", query, result.unwrapErr());
                } else {
                    m_searchResults = result.unwrapOr("Failed to parse channel search results!");
                    log::info("Channel search results: {}", m_searchResults.dump(4));
                    
                    if (m_searchResults == "Failed to parse channel search results!") {
                        log::error("Failed to parse channel search results for query {}!", query);
                        m_searchResults = matjson::Value();
                    } else {
                        log::info("Successfully retrieved search results for query {}!", query);
                        // log::info("search results: {}", m_searchResults["items"][0]["snippet"]["title"].asString().unwrapOr("No title found"));
                    }
                }
            }
        }
    });

    web::WebRequest request;
    YoutubeAPI::m_webListener.setFilter(request.get("https://www.googleapis.com/youtube/v3/search?part=snippet&q=" + query + "&key=" + m_apiKey + "&pageToken=" + pageToken)); // idk

    return m_searchResults;
}

matjson::Value YoutubeAPI::getSearchResults(std::string query) {
    m_searchResults = matjson::Value();

    YoutubeAPI::m_webListener.bind([this, query](web::WebTask::Event* e) {
        if (web::WebResponse* res = e->getValue()) { // if the download was successful
            std::string finalResult = res->string().unwrapOr("Failed to get search results!"); // final download

            if (finalResult == "Failed to get search results!") {
                log::error("Failed to get search results for query {}!", query);
            } else {
                auto result = matjson::parse(finalResult);

                if (result.isErr()) {
                    log::error("Failed to parse search results for query {}: {}", query, result.unwrapErr());
                } else {
                    m_searchResults = result.unwrapOr("Failed to parse channel search results!");
                    log::info("Channel search results: {}", m_searchResults.dump(4));
                    
                    if (m_searchResults == "Failed to parse channel search results!") {
                        log::error("Failed to parse channel search results for query {}!", query);
                        m_searchResults = matjson::Value();
                    } else {
                        log::info("Successfully retrieved search results for query {}!", query);
                        // log::info("search results: {}", m_searchResults["items"][0]["snippet"]["title"].asString().unwrapOr("No title found"));
                    }
                }
            }
        }
    });

    web::WebRequest request;
    YoutubeAPI::m_webListener.setFilter(request.get("https://www.googleapis.com/youtube/v3/search?part=snippet&q=" + query + "&key=" + m_apiKey)); // idk

    return m_searchResults;
}

matjson::Value YoutubeAPI::getSearchResults() {
    m_searchResults = matjson::Value();

    YoutubeAPI::m_webListener.bind([this](web::WebTask::Event* e) {
        if (web::WebResponse* res = e->getValue()) { // if the download was successful
            std::string finalResult = res->string().unwrapOr("Failed to get search results!"); // final download

            if (finalResult == "Failed to get search results!") {
                log::error("Failed to get search results for query {}!", m_searchQuery);
            } else {
                auto result = matjson::parse(finalResult);

                if (result.isErr()) {
                    log::error("Failed to parse search results for query {}: {}", m_searchQuery, result.unwrapErr());
                } else {
                    m_searchResults = result.unwrapOr("Failed to parse channel search results!");
                    log::info("Channel search results: {}", m_searchResults.dump(4));
                    
                    if (m_searchResults == "Failed to parse channel search results!") {
                        log::error("Failed to parse channel search results for query {}!", m_searchQuery);
                        m_searchResults = matjson::Value();
                    } else {
                        log::info("Successfully retrieved search results for query {}!", m_searchQuery);
                        // log::info("search results: {}", m_searchResults["items"][0]["snippet"]["title"].asString().unwrapOr("No title found"));
                    }
                }
            }
        }
    });

    web::WebRequest request;
    YoutubeAPI::m_webListener.setFilter(request.get("https://www.googleapis.com/youtube/v3/search?part=snippet&q=" + m_searchQuery + "&key=" + m_apiKey)); // idk

    return m_searchResults;
}