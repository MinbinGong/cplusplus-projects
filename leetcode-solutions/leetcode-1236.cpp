/*
 * 1236. Web Crawler
 *
 * Given a url startUrl and an interface HtmlParser, implement a web crawler to crawl all links that are under the same hostname as startUrl.
 *
 * Return all urls obtained by your web crawler in any order.
 *
 * Your crawler should:
 *
 * Start from the page: startUrl
 * Call HtmlParser.getUrls(url) to get all urls from a webpage of given url.
 * Do not crawl the same link twice.
 * Explore only the links that are under the same hostname as startUrl.
 *
 * As shown in the example url above, the hostname is example.org. For simplicity sake, you may assume all urls use http protocol without any port specified. For example, the urls http://leetcode.com/problems and http://leetcode.com/contest are under the same hostname, while urls http://example.org/test and http://example.com/abc are not under the same hostname.
 *
 * The HtmlParser interface is defined as such:
 *
 * interface HtmlParser {
 *   // Return a list of all urls from a webpage of given url.
 *   public List<String> getUrls(String url);
 * }
 * 
 * Note:
 * 1 <= urls.length <= 1000
 * 1 <= urls[i].length <= 300
 * startUrl is one of the urls.
 * Hostname label must be from 1 to 63 characters long, including the dots, may contain only the ASCII letters from 'a' to 'z', digits from '0' to '9' and the hyphen-minus character ('-').
 * The hostname may not start or end with the hyphen-minus character ('-'). 
 * See: https://en.wikipedia.org/wiki/Hostname#Restrictions_on_valid_hostnames
 * You may assume there're no duplicates in url library.
 * 
 */
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <regex>
#include <atomic>
#include <memory>

using namespace std;

// HtmlParser接口定义（题目提供）
class HtmlParser {
public:
    vector<string> getUrls(string url);
};

class Solution1 {
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        // 提取主机名
        string hostname = extractHostname(startUrl);
        
        // 线程安全的共享数据结构
        unordered_set<string> visited;
        queue<string> urlQueue;
        mutex mtx;
        condition_variable cv;
        int activeThreads = 0;
        bool done = false;
        
        // 初始化
        {
            lock_guard<mutex> lock(mtx);
            visited.insert(startUrl);
            urlQueue.push(startUrl);
        }
        
        // 线程池大小（根据CPU核心数调整）
        unsigned int numThreads = thread::hardware_concurrency();
        if (numThreads == 0) numThreads = 4;
        
        vector<thread> workers;
        
        // 工作线程函数
        auto worker = [&]() {
            while (true) {
                string currentUrl;
                
                // 获取下一个URL
                {
                    unique_lock<mutex> lock(mtx);
                    cv.wait(lock, [&]() {
                        return !urlQueue.empty() || done;
                    });
                    
                    if (done && urlQueue.empty()) {
                        return;
                    }
                    
                    if (!urlQueue.empty()) {
                        currentUrl = urlQueue.front();
                        urlQueue.pop();
                        activeThreads++;
                    } else {
                        continue;
                    }
                }
                
                // 获取当前页面的所有链接
                vector<string> urls = htmlParser.getUrls(currentUrl);
                
                // 处理获取到的URL
                {
                    lock_guard<mutex> lock(mtx);
                    for (const string& url : urls) {
                        // 检查是否属于同一主机名且未访问过
                        if (extractHostname(url) == hostname && 
                            visited.find(url) == visited.end()) {
                            visited.insert(url);
                            urlQueue.push(url);
                        }
                    }
                    
                    activeThreads--;
                    
                    // 如果没有活跃线程且队列为空，通知所有线程结束
                    if (activeThreads == 0 && urlQueue.empty()) {
                        done = true;
                        cv.notify_all();
                    } else if (!urlQueue.empty()) {
                        // 通知其他线程有新的URL可处理
                        cv.notify_all();
                    }
                }
            }
        };
        
        // 创建并启动工作线程
        for (unsigned int i = 0; i < numThreads; ++i) {
            workers.emplace_back(worker);
        }
        
        // 等待所有线程完成
        for (auto& t : workers) {
            t.join();
        }
        
        // 返回结果
        return vector<string>(visited.begin(), visited.end());
    }
    
private:
    // 提取URL的主机名
    string extractHostname(const string& url) {
        // 简单的正则表达式匹配主机名
        // URL格式: http://hostname/path
        regex pattern(R"(^https?://([^/]+))");
        smatch match;
        
        if (regex_search(url, match, pattern) && match.size() > 1) {
            return match[1].str();
        }
        return "";
    }
};

// 方法2：使用future和async的简化版本
class Solution2 {
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        string hostname = extractHostname(startUrl);
        unordered_set<string> visited;
        mutex mtx;
        
        function<void(string)> dfs = [&](string url) {
            // 检查是否已访问
            {
                lock_guard<mutex> lock(mtx);
                if (visited.find(url) != visited.end()) {
                    return;
                }
                visited.insert(url);
            }
            
            // 获取链接
            vector<string> urls = htmlParser.getUrls(url);
            vector<future<void>> futures;
            
            // 并发处理子链接
            for (const string& nextUrl : urls) {
                if (extractHostname(nextUrl) == hostname) {
                    futures.push_back(async(launch::async, [&, nextUrl]() {
                        dfs(nextUrl);
                    }));
                }
            }
            
            // 等待所有异步任务完成
            for (auto& f : futures) {
                f.get();
            }
        };
        
        dfs(startUrl);
        return vector<string>(visited.begin(), visited.end());
    }
    
private:
    string extractHostname(const string& url) {
        size_t start = url.find("://");
        if (start == string::npos) return "";
        start += 3;
        size_t end = url.find('/', start);
        if (end == string::npos) end = url.length();
        return url.substr(start, end - start);
    }
};

// 方法3：使用线程池和原子操作的BFS版本
class ThreadPool {
public:
    ThreadPool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] {
                            return this->stop || !this->tasks.empty();
                        });
                        if (this->stop && this->tasks.empty())
                            return;
                        task = move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
        }
    }
    
    template<class F>
    void enqueue(F&& f) {
        {
            lock_guard<mutex> lock(queue_mutex);
            tasks.emplace(forward<F>(f));
        }
        condition.notify_one();
    }
    
    ~ThreadPool() {
        {
            lock_guard<mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (thread &worker : workers)
            worker.join();
    }
    
private:
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex queue_mutex;
    condition_variable condition;
    bool stop;
};

class Solution3 {
public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        string hostname = extractHostname(startUrl);
        unordered_set<string> visited;
        mutex visited_mtx;
        atomic<int> activeTasks{0};
        
        auto pool = make_shared<ThreadPool>(thread::hardware_concurrency());
        
        function<void(string)> processUrl = [&](string url) {
            // 检查并标记为已访问
            {
                lock_guard<mutex> lock(visited_mtx);
                if (visited.find(url) != visited.end()) {
                    activeTasks--;
                    return;
                }
                visited.insert(url);
            }
            
            // 获取链接
            vector<string> urls = htmlParser.getUrls(url);
            
            // 提交子任务
            for (const string& nextUrl : urls) {
                if (extractHostname(nextUrl) == hostname) {
                    activeTasks++;
                    pool->enqueue([&, nextUrl]() {
                        processUrl(nextUrl);
                    });
                }
            }
            
            activeTasks--;
        };
        
        activeTasks++;
        pool->enqueue([&]() {
            processUrl(startUrl);
        });
        
        // 等待所有任务完成
        while (activeTasks > 0) {
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        
        return vector<string>(visited.begin(), visited.end());
    }
    
private:
    string extractHostname(const string& url) {
        size_t pos = url.find("://");
        if (pos == string::npos) return "";
        pos += 3;
        size_t end = url.find('/', pos);
        return url.substr(pos, end - pos);
    }
};

// 测试用例示例：
// 输入: 
// startUrl = "http://news.yahoo.com/news"
// htmlParser.getUrls("http://news.yahoo.com/news") 返回:
//   ["http://news.yahoo.com", "http://news.yahoo.com/news/topics/"]
// htmlParser.getUrls("http://news.yahoo.com") 返回:
//   ["http://news.yahoo.com/news", "http://news.yahoo.com/news/topics/"]
// htmlParser.getUrls("http://news.yahoo.com/news/topics/") 返回:
//   ["http://news.yahoo.com", "http://news.yahoo.com/news"]
// 输出: 
//   ["http://news.yahoo.com", "http://news.yahoo.com/news", "http://news.yahoo.com/news/topics/"]

// 复杂度分析：
// 时间复杂度：O(V + E)，其中V是访问的网页数，E是链接数
// 空间复杂度：O(V)，用于存储已访问的URL集合
// 线程安全：使用互斥锁确保共享数据结构的线程安全

// 注意事项：
// 1. 需要处理URL解析，确保只爬取相同主机名的链接
// 2. 需要避免重复爬取同一URL
// 3. 需要处理多线程同步，避免竞态条件
// 4. 需要合理设置线程池大小，避免创建过多线程
// 5. 需要处理异常情况，如网络超时等（在实际应用中）