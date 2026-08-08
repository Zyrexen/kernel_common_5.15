/* SPDX-License-Identifier: GPL-2.0 */
/*
 * selene.h — Internal header for GrayRavens Game Detection Engine
 *
 * Peer drivers (lucid, koakuma, etc.) include this header to
 * register for game start/stop notifications.  No EXPORT_SYMBOL
 * is needed because everything is built into the kernel image (=y).
 *
 * Android13-5.15 port note: peer drivers are ported ahead of selene
 * itself, so the !CONFIG_SELENE stub keeps unconditional callers
 * (e.g. kasumi's selene_register_notifier) linkable until Phase 6
 * lands selene.c.  Mirrors the hikari.h/cpufreq_zenith.h pattern.
 */
#ifndef _SELENE_H
#define _SELENE_H

#include <linux/notifier.h>
#include <linux/types.h>

/* Notifier event values */
#define SELENE_EVENT_GAME_START		1
#define SELENE_EVENT_GAME_STOP		0

#ifdef CONFIG_SELENE
/**
 * selene_register_notifier - Register for game state change events
 * @nb: notifier block to register
 *
 * Returns 0 on success, negative errno on failure.
 */
int selene_register_notifier(struct notifier_block *nb);

/**
 * selene_unregister_notifier - Unregister from game state change events
 * @nb: notifier block to unregister
 *
 * Returns 0 on success, negative errno on failure.
 */
int selene_unregister_notifier(struct notifier_block *nb);
#else
static inline int selene_register_notifier(struct notifier_block *nb)
{
	return 0;
}

static inline int selene_unregister_notifier(struct notifier_block *nb)
{
	return 0;
}
#endif /* CONFIG_SELENE */

#endif /* _SELENE_H */
