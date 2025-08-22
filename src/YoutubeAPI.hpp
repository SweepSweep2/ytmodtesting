#pragma once
#include <Geode/Geode.hpp>
#include <cocos2d.h>
#include <Geode/utils/web.hpp>
#include <matjson.hpp>

#ifdef GEODE_IS_WINDOWS
    #ifdef SWEEP_YOUTUBE_API_EXPORTS
        #define YOUTUBE_API_DLL __declspec(dllexport)
    #else
        #define YOUTUBE_API_DLL __declspec(dllimport)
    #endif
#else
    #define YOUTUBE_API_DLL __attribute__((visibility("default")))
#endif

using namespace geode::prelude;
using namespace cocos2d;

class YOUTUBE_API_DLL YoutubeAPI {
    private:
        std::string m_apiKey;
        std::string m_videoId;
        std::string m_channelId;
        std::string m_searchQuery;
        matjson::Value m_videoInfo;
        matjson::Value m_channelSubscriptions;
        matjson::Value m_searchResults;
        matjson::Value m_activities;
        matjson::Value m_captionInfo;
        matjson::Value m_commentInfo;
        matjson::Value m_comments;
        EventListener<web::WebTask> m_webListener;
    protected:
        static YoutubeAPI* instance;
    public:
        static YoutubeAPI* get();
        std::string getApiKey();
        std::string getVideoId();
        std::string getChannelId();
        std::string getSearchQuery();
        void setApiKey(std::string apiKey);
        void setVideoId(std::string videoId);
        void setChatId();
        void setChannelId(std::string channelId);
        void setSearchQuery(std::string searchQuery);
        matjson::Value getVideoInfo(std::string videoId, std::function<void(const matjson::Value&)> callback);
        matjson::Value getVideoInfo(std::function<void(const matjson::Value&)> callback);
        matjson::Value getSubscriptions(std::string channelId, std::string pageToken, std::function<void(const matjson::Value&)> callback);
        matjson::Value getSubscriptions(std::string channelId, std::function<void(const matjson::Value&)> callback);
        matjson::Value getSubscriptions(std::function<void(const matjson::Value&)> callback);
        matjson::Value getSearchResults(std::string query, std::string pageToken, std::function<void(const matjson::Value&)> callback);
        matjson::Value getSearchResults(std::string query, std::function<void(const matjson::Value&)> callback);
        matjson::Value getSearchResults(std::function<void(const matjson::Value&)> callback);
        matjson::Value getActivites(std::string channelId, std::string pageToken, std::function<void(const matjson::Value&)> callback);
        matjson::Value getActivites(std::string channelId, std::function<void(const matjson::Value&)> callback);
        matjson::Value getActivites(std::function<void(const matjson::Value&)> callback);
        matjson::Value getCaptionInfo(std::string videoId, std::function<void(const matjson::Value&)> callback);
        matjson::Value getCaptionInfo(std::function<void(const matjson::Value&)> callback);
        matjson::Value getCommentFromId(std::string commentId, std::function<void(const matjson::Value&)> callback);
        matjson::Value getComments(std::string parentId, std::string pageToken, std::function<void(const matjson::Value&)> callback);
        matjson::Value getComments(std::string parentId, std::function<void(const matjson::Value&)> callback);
        matjson::Value getComments(std::function<void(const matjson::Value&)> callback);
};