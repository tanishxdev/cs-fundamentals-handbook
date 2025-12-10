# Long Polling vs WebSockets vs Server-Sent Events

Real-time means:

* Client should get updates **immediately** when server has new data.
* No delay, no constant refreshing.

These three techniques are used to achieve real-time communication.

* Long Polling
* SSE (Server-Sent Events)
* WebSockets

All three solve the **same goal** but in **different ways**.

---

# 1. Problem We Are Solving

You have apps like:

* Chat applications
* Live score updates
* Stock price tickers
* Notification systems
* Multiplayer games

The problem:

**How can server send new data to client instantly?**

By default, HTTP is **request → response** only.
But real-time apps need:

**Server → Client push**

So we use one of these 3 methods.

---

# 2. Long Polling (Oldest Technique)

![](https://sendbird.imgix.net/cms/Tutorial-image_How-long-polling-works.png)
![](https://substackcdn.com/image/fetch/$s_!3PVv!,w_1200,h_600,c_fill,f_jpg,q_auto:good,fl_progressive:steep,g_auto/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2F90181ae6-4dcb-456f-a43a-7824d97c740b_2002x1472.png)

## Concept (Very Simple)

Client keeps asking server like this:

"Do you have new data?"
"Do you have new data?"
"Do you have new data?"

But instead of replying immediately, server **waits** for new data and then replies.

This makes it “almost” real-time.

## Why Long Polling Became Popular

Earlier browsers and servers **could NOT** keep open connections for long.
So long polling was the only trick to simulate live updates.

## How It Actually Works (Step-by-Step)

1. Client sends a request → `/updates`
2. Server checks:

   * If data exists → send immediately
   * If no data → **hold request** (wait 30–60 seconds)
3. When server finally sends response, client **immediately sends another request**
4. Loop continues forever

This creates the real-time feeling.

## Example Code

### Client

```js
function longPoll() {
  fetch("/updates")
    .then(res => res.json())
    .then(data => {
      console.log("New data:", data);
      longPoll(); // continue the long-poll cycle
    });
}

longPoll();
```

### Server

```js
function handleLongPoll(req, res) {
  waitUntil(newMessage OR timeout);

  res.send(newMessage || { empty: true });
}
```

## When Should You Use Long Polling?

* Your system is simple
* You want 100% browser support
* Your server traffic is low
* Firewalls block WebSockets

Good for:

* Notifications
* Basic updates
* Legacy systems

Not good for large-scale apps because it creates **too many repeated HTTP calls**.

---

# 3. SSE (Server-Sent Events)

![](https://miro.medium.com/v2/resize:fit:1400/1*ZOvd7h41rtYPVvxUcyP5Kw.png)
![](https://bunnyacademy.b-cdn.net/What-is-SSE-Server-Sent-Events-and-how-do-they-work.svg)
## Concept (Very Simple)

SSE means:

**Server keeps one connection open and continuously sends events to the client.**

Client cannot send messages back using the same connection.

So direction is:

Server → Client only.

## Why SSE Exists

* Very lightweight
* Works over normal HTTP
* Perfect for dashboards and streaming logs

## How It Works (Simple Flow)

1. Client opens an `EventSource` connection
2. Server sets `Content-Type: text/event-stream`
3. Server keeps connection open forever
4. Server pushes events like:

```
data: { "price": 100 }
```

5. Browser receives them instantly

## Code Example

### Client

```js
const stream = new EventSource("/stream");

stream.onmessage = (event) => {
  console.log("Received:", event.data);
};
```

### Server

```js
res.setHeader("Content-Type", "text/event-stream");

eventEmitter.on("event", (data) => {
  res.write("data: " + JSON.stringify(data) + "\n\n");
});
```

## When Should You Use SSE?

* Live dashboards
* Monitoring logs
* Stock tickers
* Notification streams
* When you only need one-way updates

Not suitable for:

* Chat app
* Games
* Video calls
  Because client also needs to send data back quickly.

---

# 4. WebSockets (Most Powerful Real-Time Method)
![](https://substackcdn.com/image/fetch/$s_!-4x2!,f_auto,q_auto:good,fl_progressive:steep/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2Fd58bb11f-3727-4ed2-bcbd-dbffe55069c7_1076x1086.png)
![](https://substackcdn.com/image/fetch/$s_!4K1s!,f_auto,q_auto:good,fl_progressive:steep/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2F95e05d09-d4fb-460b-97c6-19406212c673_1546x1606.png)
## Concept (Very Simple)

**WebSocket = permanent, two-way connection.**

Both sides can send messages anytime.

Server ↔ Client
Not request/response.

## Why WebSockets Are Needed

You need this when:

* Chat systems
* Real-time gaming
* Collaborative editing
* Trading dashboards (super low latency)

WebSockets can handle thousands of messages per second easily.

## How It Works (Clear Steps)

1. Client asks server to upgrade HTTP → WebSocket
2. Server accepts handshake
3. Now both talk freely
4. Connection stays open unless closed

## Code Example

### Client

```js
const ws = new WebSocket("ws://localhost:3000");

ws.onmessage = (msg) => {
  console.log("Received:", msg.data);
};

ws.send("Hello Server");
```

### Server

```js
wsServer.on("connection", (socket) => {
  socket.send("Connected");

  socket.on("message", (msg) => {
    console.log("Client:", msg);
  });
});
```

## When Should You Use WebSockets?

* Chat apps
* Multiplayer games
* Real-time collaboration
* High-frequency trading apps
* Anything requiring **two-way** communication

But:

* Harder to scale
* Load balancers must support WebSockets

---

# 5. Comparison Table (Ultra Clear)

| Feature         | Long Polling                | SSE                  | WebSockets                  |
| --------------- | --------------------------- | -------------------- | --------------------------- |
| Connection      | Repeated requests           | Single HTTP stream   | Full-duplex TCP             |
| Direction       | Server → Client (fake push) | Server → Client only | Server ↔ Client both ways   |
| Latency         | Medium                      | Low                  | Very Low                    |
| Efficiency      | Low                         | Medium               | High                        |
| Complexity      | Easy                        | Medium               | Harder                      |
| Browser Support | 100%                        | Most browsers        | Modern browsers             |
| Best Use Case   | Notifications, fallback     | Live dashboards      | Chats, games, realtime apps |

---

# 6. Which One Should YOU Use?

### Need two-way real-time?

Use **WebSockets**

### Need only server-to-client streaming?

Use **SSE**

### Need simplest solution or fallback?

Use **Long Polling**

---

# 7. LLD Concepts Involved (Important for System Design)

These techniques connect with core LLD ideas:

* Connection lifecycle
* Event-driven architecture
* Observer / Pub-Sub pattern
* Backpressure handling
* Heartbeat / ping-pong
* Message queue integration
* Scaling with Redis / Kafka
* Load balancing long-lived connections

Real interviews love these topics because they test:

**Real-time system design understanding.**

---

# 8. Super Easy Analogies

## Long Polling

You keep calling the shop every few minutes:
"Is my order ready?"

## SSE

Your friend keeps sending you updates.
You only listen.

## WebSockets

A phone call.
Both people can talk anytime.

---

# 9. Simple Memory Trick

| Long Polling | SSE            | WebSocket         |
| ------------ | -------------- | ----------------- |
| Keep asking  | Keep listening | Live conversation |

---

