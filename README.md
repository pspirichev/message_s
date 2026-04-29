# message_s

**message_s** is a high-performance, open-source messaging server designed for small groups (~100 users) who prioritize absolute privacy and data sovereignty. Built with C++20, it provides a lightweight yet "hardened" infrastructure for end-to-end encrypted (E2EE) communication.

Unlike centralized platforms, this project is built for self-hosting, giving you full control over your messages, storaging and routing. 

## Features

- Full self host solution
- Works without external DNS names and certificates, all you need is any hardware running linux and have IP adress
- Low resource consumtion
- Three-Layerd security with TLS + Double Ratchet E2EE + SHA256 data integrity check
- ed25519 authentification
- Message compression

## FAQ

#### Why is this project needed?

To enable communication in absolutely any network, whether restricted, local, or insecure, while maintaining message privacy, high connectivity, and independence from external services.

#### What do I need to start communicating?

A network of devices supporting the TCP/IP stack, one of which will run a server, and some free time.

## Quick start guide

- Install and configure a server or find an existing server to chat on
- Install the client application
- Create your user
- Create or request an invite to the server of your choice
- Connect to the server
- Select another user on the server with whom you want to chat
- Chat!

## License

[This project is licensed under the GNU Affero General Public License v3.0 (AGPL-3.0) - see the LICENSE file of this link for details.](https://www.gnu.org/licenses/agpl-3.0.html)
- AGPLv3 license: all server modifications must be open source, even when used in the cloud (SaaS).
- Self-host freedom: you can freely deploy and modify the server on your own premises.
- Open Contribution: any accepted changes to the server core remain protected by AGPLv3.
- Forking rules: Forking is permitted only as long as the AGPLv3 license is maintained.


## Author and Feedback

2026 Telegram: @wlm1861

[RU Translation / Перевод на русский язык](https://github.com/pspirichev/message_s/tree/developer/docs/README.ru.md)