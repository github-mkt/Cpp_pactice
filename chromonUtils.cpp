namespace helpers
{
struct Metrics {
    double averageBitrate;
    float averageFramerate;
    std::uint32_t sampleCount;
    std::chrono::milliseconds elapsedTime;
}
  std::string toString(const Metrics &metrics);
 
  std::ostream &operator<<(std::ostream &os, const Metrics &metrics);
  
  void :onDataReceivedCallback(const std::uint8_t *buffer, std::int64_t bufferSize)
{

    std::unique_lock<std::mutex> lock(_callbackEvent.mutex);
    if (_callbackEvent.callback == nullptr) {
        return;
    }
    _callbackEvent.callback(buffer, bufferSize);
}

  void registerBufferReceivedCallback(std::function<void(const uint8_t *, int64_t)> callback)
{
    std::unique_lock<std::mutex> lock(_callbackEvent.mutex);
    _callbackEvent.callback = callback;
    lock.unlock();

    _callbackEvent.condition.notify_one();
}
  
   struct ReceiveCallbackAvailable {
        std::function<void(const std::uint8_t *, std::int64_t)> callback;
        std::mutex mutex;
        std::condition_variable condition;
    };
  
  
     [[nodiscard]] Metrics calculateMetrics(std::uint64_t totalSize, std::chrono::milliseconds exactInterval) const;

    OnMeasure _onMeasure{};
    bool _running{};

    struct FrameInfo {
        std::uint64_t size{};
        Clock::time_point prevTimestamp;
    };
    FixedSizeQueue<FrameInfo> _queue;
    Clock::time_point _prevTimestamp{};
};

